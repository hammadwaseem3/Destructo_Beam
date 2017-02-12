#ifndef MAP_H
#define MAP_H


#include <array>
#include <iostream>
#include <irrlicht.h>  //irrlicht library include
#include "health.h"
using namespace std;    //some namespace of irrlict
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")    //it is used to include irrlicht.dll file which must include to use irrlicht
#endif




class Map:public IEventReceiver,public health
{
	private:
	
		IVideoDriver* driver;    //video driver responsible to display(in device)
		scene::ISceneManager* smgr;     //scene manager resposible for editing or using models,maps etc
		IrrlichtDevice *device;
		ITriangleSelector* selector;    //it is for collision 
		ITriangleSelector* model_selector;   // these for collision with models
		ITriangleSelector* d_selector;
		ITriangleSelector* demon_selector;
		ITriangleSelector* imp_selector;
		ITriangleSelector* warroir_selector;
		ITriangleSelector* s_selector;
		ITriangleSelector* fatso_selector;
		
		IAnimatedMesh* mesh_n;         // construct of vertices, faces, and edges that defines the shape of an object
		IAnimatedMeshSceneNode* node_n;  //node is used to perform animation or many thing simply for use a model
		IAnimatedMesh* mesh_s;
		IAnimatedMeshSceneNode* node_s;
		IAnimatedMesh* mesh_w;
		IAnimatedMeshSceneNode* node_w;
		IAnimatedMesh* mesh_d;
		IAnimatedMeshSceneNode* node_d;
		IAnimatedMesh* mesh_i;
		IAnimatedMeshSceneNode* node_i;
		IAnimatedMesh* mesh_fatso;
		IAnimatedMeshSceneNode* node_fatso;
        IAnimatedMesh* mesh_monkey ;
		IAnimatedMeshSceneNode* node_monkey ;
		
		int count_model;   //this is used for count a bullet attack on model
		int count_d;
		int count_demon;
		int count_imp;
		int count_warroir;
		int count_fatso;
		int count_s;

		ICameraSceneNode* camera ;   //this is camera    
		ITriangleSelector* mapSelector;   //collision
		
		
	
public:
	void setMap();  //set all things like collision,models,map etc

	void model();  //introduce model

	void model_play();   //move models
	
	void model_ninja();
	
	void model_play_ninja(int x , int y , int z);

	void model_s();

	void model_play_s(int x , int y , int z);


	void model_warroir();

	void model_play_w(int x , int y , int z);
	
	void model_demon();

	void model_play_d(int x , int y , int z);

	void model_imp();

	void model_play_i(int x , int y , int z);

	void model_fatso();

	void model_play_fatso(int x , int y , int z);

	void exeMap();  //execute map

	void playMap();   //play map in game loop

	bool d();  //chcking purpose
	
	void drop();  //drop device
	
	bool OnEvent(const SEvent& event);  //it is responsible of every event in game either mouse click
	
	void shoot();  //shooting
	
};

#endif