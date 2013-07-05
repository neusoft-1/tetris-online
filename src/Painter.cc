#include "Painter.h"
#include "Singleton.h"
#include "GlobalSettings.h"
#include<assert.h>
Painter::Painter(paint_func &func)
	:window_width(Singleton<GlobalSettings>::instance().window_width),
	window_height(Singleton<GlobalSettings>::instance().window_height)
{
	setColor = func.setColor;
	fillRect = func.fillRect;
}

Painter::~Painter()
{

}

void Painter::getImageId(char block_type)
{
	auto img_id;
	switch(block_type)
	{
		case data::box::I :
			img_id = img_id_list[0];
			break;
		case data::box::J :
			img_id = img_id_list[1];
			break;
		case data::box::L :
			img_id = img_id_list[2];
			break;
		case data::box::O :
			img_id = img_id_list[3];
			break;
		case data::box::S :
			img_id = img_id_list[4];
			break;		
		case data::box::Z :
			img_id = img_id_list[5];
			break;
		case data::box::T :
			img_id = img_id_list[6];
			break;
		default:
			img_id = NULL;
	}
	return img_id;
}

void Painter::paintBlock(int offset_x,int offset_y,int x_index,int y_index,int block_img_id){
	if(block_img_id != NULL){
		int height,width;
		//TODO : caculate the block size & the position to paint from the window size
		width = 800/40;
		height = 600/30;
		paintImage( x_index * width + offset_x , y_index * height + offset_y , width , height , block_img_id);
	}
}

void Painter::paintSingle(int offset_x,int offset_y,const TetrisData *data)
{
	auto static_box_data = data->get_static();
	for(auto iter = static_box_data.begin(),i=0; iter!=static_box_data.end(); ++iter,++i){
		for(int j=0; j<data::ROW; j++){
			auto img_id = getImageId((*iter).line[j]);
			paintBlock( offset_x , offset_y , static_box_data.size() - i , j , img_id );
		}
	}
	auto mov_box_data = data->get_mov().toArray();
	//TODO : finish drawring the moving boxes
}

void Painter::paintBackground(){
	paintImage(0,0,window_width,window_height,background_img_id);
}

void Painter::resizeWindow(int width,int height)
{
	window_width = width;
	window_height = height;
}

void Painter::paintOnline()
{
	assert(self_data&&other_data);
	//setColor(255, 0, 0, 255);
	//fillRect(0,0,100,100);
	paintBackground();
	//TODO : calulate the offset from the window size
	int left_box_offset_left = 50;
	int right_box_offset_left = 450;
	int box_top_offset = 50;

	paintSingle(left_box_offset_left , box_top_offset , self_data);
	paintSingle(right_box_offset_left , box_top_offset , other_data);
}

void Painter::init()
{
	//TODO : Load the image from the resource files.
	img_id_list[0] = loadImage("I.png");
	img_id_list[1] = loadImage("J.png");
	img_id_list[2] = loadImage("L.png");
	img_id_list[3] = loadImage("O.png");
	img_id_list[4] = loadImage("S.png");
	img_id_list[5] = loadImage("Z.png");
	img_id_list[6] = loadImage("T.png");
	background_img_id = loadImage("background.png");
}

void Painter::setData(const TetrisData *self_data, const TetrisData *other_data)
{
	this->self_data = self_data;
	this->other_data = other_data;
}
