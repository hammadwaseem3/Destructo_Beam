#include "Map.h" 



static int n = 1 ;

std::array <int,15> x_cordinate = {140,-1000,-450,210,210,-700,140,140,-540,-940,-1800,-3000,-3000,-1200,-3000}; //array for x-cordinate by which model is randomly place
std::array <int,15> y_cordinate = {-280,-150,-20,-135,-135,-150,-180,-10,0,-250,-250,-145,-145,-140,-15};        //array for y-cordinate by which model is randomly place
std::array <int,15> z_cordinate = {-700,-1000,-100,0,0,-1300,500,1750,1400,900,1100,1100,-1000,-1200,-1900};     //array for z-cordinate by which model is randomly place

int array_num=0;   //array selection
int score_num=0;   
std::array <int,5> score_array= {0,0,0,0,0};   

int j=0,x=700,y=0;

void Map::setMap()
{
	count_model= 0;   //intilaize to zero 
	count_d= 0;
	count_demon= 0;
	count_imp= 0;
	count_warroir = 0;
	count_s = 0;
	count_fatso = 0 ;
	
	device = createDevice(EDT_OPENGL, dimension2d<u32>(1500, 880),16,true,false , false ,this);  //create device for game
	driver = device->getVideoDriver();  //create driver
	smgr = device->getSceneManager();   //create scenemanager
	setHealth ();  //set health
	
		
	selector = 0;  //intiliaze to 0
	SKeyMap keyMap[10];  // set key 
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_UP;
    keyMap[1].Action = EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = KEY_KEY_W;
    keyMap[2].Action = EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = KEY_DOWN;
    keyMap[3].Action = EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = KEY_KEY_S;
    keyMap[4].Action = EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = KEY_LEFT;
    keyMap[5].Action = EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = KEY_KEY_A;
    keyMap[6].Action = EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = KEY_RIGHT;
    keyMap[7].Action = EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = KEY_KEY_D;
    keyMap[8].Action = EKA_JUMP_UP;
    keyMap[8].KeyCode = KEY_KEY_J;
    keyMap[9].Action = EKA_CROUCH;
    keyMap[9].KeyCode = KEY_KEY_C;

	camera =smgr->addCameraSceneNodeFPS(0, 100.0f, 0.6f, -1, keyMap, 10, false, 2.2f);  //add a camera and attach key with it
	
	IAnimatedMeshMD2* weaponMesh = (IAnimatedMeshMD2*) smgr->getMesh("Media/gun.md2");  //get gun

	model_demon(); //call all model function
	model_imp();
	model();
	model_fatso();
    model_ninja(); 
	model_s();
	model_warroir();

	IAnimatedMesh* mesh_motor = smgr->getMesh("Media/motor.md2"); //get motor bike
	IAnimatedMeshSceneNode* node_motor = smgr->addAnimatedMeshSceneNode( mesh_motor ); //create node and attach it with motor mesh
	node_motor->setScale(vector3df(2));//set scale in map
	node_motor->setPosition(vector3df(-3200,-15,-2000)); //set position
	node_motor->setRotation(vector3df(0,90,0)); //set rotation
	node_motor->setAnimationSpeed(8.f); //set animation speed
	node_motor->getMaterial(0).NormalizeNormals = true; //get material texture
	node_motor->getMaterial(0).Lighting = true; //lighting the model
	model_selector = smgr->createTriangleSelector(node_motor);  //create triangle for collision
	node_motor->setTriangleSelector(model_selector); // set triangle selector with model 
	if (node_motor)
	{
		node_motor->setMaterialFlag(EMF_LIGHTING, false); 
		node_motor->setMD2Animation(EMAT_STAND); //put animation in models
		node_motor->setMaterialTexture( 0, driver->getTexture("Media/motor.jpg") ); //get picture of model and wrap it with mesh
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(model_selector, camera, vector3df(30,50,30), vector3df(0,0,0), vector3df(0,30,0));  //create collision responce with camera

		model_selector->drop(); // As soon as we're done with the selector, drop it.

		camera->addAnimator(anim); //attach collision responce with camera

		anim->drop();  // And  drop the animator when we are done referring to it.
	}


	IAnimatedMesh* mesh_Truck = smgr->getMesh("Media/Truck.md2");  //same as above
	IAnimatedMeshSceneNode* node_Truck = smgr->addAnimatedMeshSceneNode( mesh_Truck  );
	node_Truck->setScale(vector3df(2));
	node_Truck->setPosition(vector3df(-1000,-180,-1900));
	node_Truck->setRotation(vector3df(9,0,0));
	node_Truck->setAnimationSpeed(8.f);
	node_Truck->getMaterial(0).NormalizeNormals = true;
	node_Truck->getMaterial(0).Lighting = true;
	model_selector = smgr->createTriangleSelector(node_Truck);
	node_Truck->setTriangleSelector(model_selector);
	if (node_Truck)
	{
		node_Truck->setMaterialFlag(EMF_LIGHTING, false);
		node_Truck->setMD2Animation(EMAT_STAND);
		node_Truck->setMaterialTexture( 0, driver->getTexture("Media/Truck.png") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(model_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));
		model_selector->drop();
		camera->addAnimator(anim);
		anim->drop();  
		
    if ( 0 == weaponMesh )
	{
		return;
	}

	IAnimatedMeshSceneNode* WeaponNode;
	WeaponNode = smgr->addAnimatedMeshSceneNode( weaponMesh,camera,10, vector3df( 0, 0, 0),vector3df(-90,-90,90)); //attach gun with camera
    WeaponNode->setMaterialFlag(EMF_LIGHTING, false);
	WeaponNode->setMD2Animation(EMAT_STAND);
    WeaponNode->setMaterialTexture(0, driver->getTexture( "Media/gun.jpg")); //wrap picture on weponmesh
	
}
}
void Map::model()
{
	mesh_monkey = smgr->getMesh("Media/monkey.md2"); //same as above
	node_monkey = smgr->addAnimatedMeshSceneNode( mesh_monkey  );
	
	node_monkey->setScale(vector3df(2));
	node_monkey->setPosition(vector3df(-500,-150,-300));
	node_monkey->setRotation(vector3df(0,0,0));
	node_monkey->setAnimationSpeed(8.f);
	node_monkey->getMaterial(0).NormalizeNormals = true;
	node_monkey->getMaterial(0).Lighting = true;
	model_selector = smgr->createTriangleSelector(node_monkey);
	node_monkey->setTriangleSelector(model_selector);

	if (node_monkey)
	{
		node_monkey->setMaterialFlag(EMF_LIGHTING, false);
		node_monkey->setMD2Animation(EMAT_STAND );
		node_monkey->setMaterialTexture( 0, driver->getTexture("Media/monkey.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(model_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));

		model_selector->drop(); 
		
		
		camera->addAnimator(anim);
		
		anim->drop();  
		
	}
}

void Map::model_play()
{
	vector3df waypoint[2]; //create vector 
	
	waypoint[0].set(camera->getPosition ());  //set vector
	waypoint[1].set(camera->getPosition ());
	
	ISceneNodeAnimator* anim1 ; 

	anim1 = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true); //add animator
	node_monkey->addAnimator(anim1); //attach it with model 
	anim1->drop();
	
}
void Map::model_ninja()
{
	mesh_n= smgr->getMesh("Media/dwarf.x");

	node_n = smgr->addAnimatedMeshSceneNode( mesh_n  );
	node_n->setScale(vector3df(2));
	node_n->setPosition(vector3df(140,-10,1750));
	node_n->setRotation(vector3df(9,0,0));
	node_n->setAnimationSpeed(8.f);
	node_n->getMaterial(0).NormalizeNormals = true;
	node_n->getMaterial(0).Lighting = true;

	d_selector = smgr->createTriangleSelector(node_n);
	node_n->setTriangleSelector(d_selector);
	if (node_n)
	{
		node_n->setMaterialFlag(EMF_LIGHTING, false);
		node_n->setMD2Animation(EMAT_RUN );
		node_n->setMaterialTexture( 0, driver->getTexture("Media/dwarf.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(d_selector, camera, vector3df(30,50,30),
		vector3df(0,0,0), vector3df(0,30,0));
	
		d_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop();  
		
	}
	
}
void Map::model_play_ninja(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);

	ISceneNodeAnimator* anim1 ; 

	anim1 = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_n->addAnimator(anim1);
	anim1->drop();
	
}


void Map::model_s()
{
	mesh_s= smgr->getMesh("Media/Samourai.md2");
	
	node_s = smgr->addAnimatedMeshSceneNode( mesh_s  );
	node_s->setScale(vector3df(2));
	node_s->setPosition(vector3df(-540,0,1400));
	node_s->setRotation(vector3df(9,0,0));
	node_s->setAnimationSpeed(8.f);
	node_s->getMaterial(0).NormalizeNormals = true;
	node_s->getMaterial(0).Lighting = true;
	
	s_selector = smgr->createTriangleSelector(node_s);
	node_s->setTriangleSelector(s_selector);
	
	if (node_s)
	{
		node_s->setMaterialFlag(EMF_LIGHTING, false);
		node_s->setMD2Animation(EMAT_STAND);
		node_s->setMaterialTexture( 0, driver->getTexture("Media/Samourai.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(s_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));

		s_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop();  
		
	}


}
void Map::model_play_s(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);
	
	ISceneNodeAnimator* anims ;
		
	anims = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_s->addAnimator(anims);
	
	anims->drop();
	
}

void Map::model_warroir()
{
	mesh_w = smgr->getMesh("Media/warrior.md2");
	
	node_w = smgr->addAnimatedMeshSceneNode( mesh_w  );
	node_w->setScale(vector3df(2));
	node_w->setPosition(vector3df(-940,-250,900));
	node_w->setRotation(vector3df(9,0,0));
	node_w->setAnimationSpeed(8.f);
	node_w->getMaterial(0).NormalizeNormals = true;
	node_w->getMaterial(0).Lighting = true;

	warroir_selector = smgr->createTriangleSelector(node_w);
	node_w->setTriangleSelector(warroir_selector);
	if (node_w)
	{
		node_w->setMaterialFlag(EMF_LIGHTING, false);
		node_w->setMD2Animation(EMAT_STAND );
		node_w->setMaterialTexture( 0, driver->getTexture("Media/warrior.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(warroir_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));
	
		warroir_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop();  
		}
}
void Map::model_play_w(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);

	ISceneNodeAnimator* animw ; 

	animw = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_w->addAnimator(animw);
		
	animw->drop();
	
}

void Map::model_demon()
{
	mesh_d= smgr->getMesh("Media/cyber.md2");

	node_d = smgr->addAnimatedMeshSceneNode( mesh_d  );
	node_d->setScale(vector3df(2));
	node_d->setPosition(vector3df(-1800,-250,1100));
	node_d->setRotation(vector3df(0,50,0));
	node_d->setAnimationSpeed(8.f);
	node_d->getMaterial(0).NormalizeNormals = true;
	node_d->getMaterial(0).Lighting = true;

	demon_selector = smgr->createTriangleSelector(node_d);
	node_d->setTriangleSelector(demon_selector);
	
	if (node_d)
	{
		node_d->setMaterialFlag(EMF_LIGHTING, false);
		node_d->setMaterialTexture( 0, driver->getTexture("Media/cyber.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(demon_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));

		demon_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop();
			
	}
}
void Map::model_play_d(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);
	
	ISceneNodeAnimator* animd ;
		
	animd = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_d->addAnimator(animd);
	
	animd->drop();
	
}

void Map::model_imp()
{
	mesh_i= smgr->getMesh("Media/Imp.md2");

	node_i = smgr->addAnimatedMeshSceneNode( mesh_i  );
	node_i->setScale(vector3df(2));
	node_i->setPosition(vector3df(-3000,-145,1100));
	node_i->setRotation(vector3df(0,50,0));
	node_i->setAnimationSpeed(8.f);
	node_i->getMaterial(0).NormalizeNormals = true;
	node_i->getMaterial(0).Lighting = true;

	imp_selector = smgr->createTriangleSelector(node_i);
	node_i->setTriangleSelector(imp_selector);
	
	if (node_i)
	{
		node_i->setMaterialFlag(EMF_LIGHTING, false);
		node_i->setMaterialTexture( 0, driver->getTexture("Media/Imp.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(imp_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));
	
		imp_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop(); 
		}
}
void Map::model_play_i(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);

	ISceneNodeAnimator* animi ;
		
	animi = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_i->addAnimator(animi);
		
	animi->drop();
	
}

void Map::model_fatso()
{
	mesh_fatso = smgr->getMesh("Media/fatso.md2");
	node_fatso = smgr->addAnimatedMeshSceneNode( mesh_fatso  );
	
	node_fatso->setScale(vector3df(2));
	node_fatso->setPosition(vector3df(-3000,-145,-1000));
	node_fatso->setRotation(vector3df(0,50,0));
	node_fatso->setAnimationSpeed(8.f);
	node_fatso->getMaterial(0).NormalizeNormals = true;
	node_fatso->getMaterial(0).Lighting = true;

	fatso_selector = smgr->createTriangleSelector(node_fatso);
	node_fatso->setTriangleSelector(fatso_selector);
	if (node_fatso)
	{
		node_fatso->setMaterialFlag(EMF_LIGHTING, false);
		node_fatso->setMaterialTexture( 0, driver->getTexture("Media/fatso.jpg") );
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(fatso_selector, camera, vector3df(30,50,30),vector3df(0,0,0), vector3df(0,30,0));
	

		fatso_selector->drop(); 
		
		camera->addAnimator(anim);
		
		anim->drop();  
		}
}

void Map::model_play_fatso(int x , int y , int z)
{
	vector3df waypoint[2];
	
	waypoint[0].set(x,y,z);
	waypoint[1].set(x,y,z);

	ISceneNodeAnimator* animf ;

	animf = device->getSceneManager()->createFlyStraightAnimator(waypoint[0], waypoint[1], 2000, true);
	node_fatso->addAnimator(animf);
	animf->drop();
}


void Map::exeMap()
{
	device->getFileSystem()->addFileArchive("Media/map_oxodm1.pk3");  //add a map on device
	IAnimatedMesh* mesh = smgr->getMesh("Media/oxodm1.bsp");   //get mesh of map
    IMeshSceneNode* node = 0;
	

    if (mesh)
    {
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0,  -1, 1024);//intiliaze node with map
	}
	
	if (node)
	{
		node->setPosition(vector3df(-1300,-144,-1249));  //set position
		selector = smgr->createOctreeTriangleSelector(node->getMesh(), node, 128); //create triangle selector for collision with map
		node->setTriangleSelector(selector);   //set this selector with map
		camera->setPosition(vector3df(50,50,-60));
		camera->setTarget(vector3df(-70,30,-60));
	}
	
	if (selector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, camera, vector3df(30,50,30),vector3df(0,-10,0), vector3df(0,30,0)); //create collision responce animator
		selector->drop(); 
		camera->addAnimator(anim);
        anim->drop();  
		}
	
	device->getCursorControl()->setVisible(false);
	mapSelector = smgr->createOctreeTriangleSelector(mesh->getMesh(0),node, 128);
	
}
void Map::playMap()
{
		ITexture* score_pic = driver->getTexture("Media/score.jpg"); //set picture
	    driver->draw2DImage(score_pic, position2d<s32>(500, 0));
		driver->endScene();

		ITexture* health = driver->getTexture("Media/100.png");
		driver->draw2DImage(health, position2d<s32>(70, 800));
		driver->endScene();

		ITexture* plus = driver->getTexture("Media/plus.png");
		driver->draw2DImage(plus, position2d<s32>(0, 800));
		driver->endScene();

		int temp=score_num;

		for(int i =score_num ; i > 0 ; i= i/10)  // logic define for score
		{
		
			if(j>0)
			{
				x=x-20;
			}

			score_array[j]= temp % 10;
			temp=temp/10;
		
			if(score_array[j] == 0)
			{
				ITexture* score = driver->getTexture("Media/0_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 1)
			{
				ITexture* score = driver->getTexture("Media/1_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 2)
			{
				ITexture* score = driver->getTexture("Media/2_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 3)
			{
				ITexture* score = driver->getTexture("Media/3_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}
	
			if(score_array[j] == 4)
			{
				ITexture* score = driver->getTexture("Media/4_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 5)
			{
				ITexture* score = driver->getTexture("Media/5_s.jpg");   
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 6)
			{
				ITexture* score = driver->getTexture("Media/6_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}
	
			if(score_array[j] == 7)
			{
				ITexture* score = driver->getTexture("Media/7_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}
		
			if(score_array[j] == 8)
			{
				ITexture* score = driver->getTexture("Media/8_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			if(score_array[j] == 9)
			{
				ITexture* score = driver->getTexture("Media/9_s.jpg");   
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}
	
			if(score_array[j] == 10)
			{
				ITexture* score = driver->getTexture("Media/10_s.jpg");
				driver->draw2DImage(score, position2d<s32>(x, y));
				driver->endScene();
			}

			j++;
		
		}

		j=0;
		x=700;
		//bullet display 
		if(n == 1)
		{
			ITexture* num = driver->getTexture("Media/1.jpg");   
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }

	   if(n==2)
		{
			ITexture* num = driver->getTexture("Media/2.jpg");
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }

	   if(n==3)
		{
			ITexture* num = driver->getTexture("Media/3.jpg");
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }

	   if(n==4)
		{
			ITexture* num = driver->getTexture("Media/4.jpg");
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }

	   if(n==5)
		{
			ITexture* num = driver->getTexture("Media/5.jpg");
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }
	   
	   if(n==6)
		{
			ITexture* num = driver->getTexture("Media/6.jpg");
			driver->draw2DImage(num, position2d<s32>(0 , 0));
			driver->endScene();
	    }
	   
	   if(n==7)
		{
			ITexture* num = driver->getTexture("Media/7.jpg");
			driver->draw2DImage(num, position2d<s32>(0 , 0));
			driver->endScene();
	    }

	   if(n==8)
		{	
			ITexture* num = driver->getTexture("Media/8.jpg");
			driver->draw2DImage(num, position2d<s32>(0, 0));
			driver->endScene();
	    }

	   if(n==9)
		{
			ITexture* num = driver->getTexture("Media/9.jpg");
			driver->draw2DImage(num, position2d<s32>(0 , 0));
			driver->endScene();
	    }

	   if(n==10)
		{
			ITexture* num = driver->getTexture("Media/10.jpg");
			driver->draw2DImage(num, position2d<s32>(0 , 0));
			driver->endScene();
	    }

		if(n > 10)
		{
			ITexture* num = driver->getTexture("Media/0.jpg");
			driver->draw2DImage(num, position2d<s32>(0 , 0));
			driver->endScene();
	    }

	
		driver->beginScene(true, true, SColor(255,200,200,200)); //begin scene
        smgr->drawAll(); //draw all 
		driver->endScene();
}


bool Map::d()
{
		return device->run(); //return if device is running or not
}


void Map::drop()
{
		device->drop(); //drop the device
}


bool Map::OnEvent(const SEvent& event) //responsible for every event occur in game
{

	if (((event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_SPACE && event.KeyInput.PressedDown == false) ||(event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)) )
	{
		//if mouse L click is press this execute
		if ( n <= 10 )
		{
			shoot();
			n++ ;
		}

		return true;
	}


	if (((event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_KEY_R && event.KeyInput.PressedDown == false)) )
	{
		//if R is pressed
		n = 1 ;
		return true;
	}

	if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE && event.KeyInput.PressedDown == false)
	{
		//if ESC is press this will execute
		device->closeDevice();
	}

	return false;
}
	

void Map::shoot() 
{
	struct SParticleImpact  //structure hold all details of fire
	{
		u32 when;
		vector3df pos;
		vector3df outVector;
	};

	core::array<SParticleImpact> Impacts; //create an array
	
	SParticleImpact imp; //create structre
	imp.when = 0;

	// get line of camera
	vector3df start = camera->getPosition();

	vector3df end = (camera->getTarget() - start);
	end.normalize();
	start += end*8.0f; //speed of firing
	end = start + (end * camera->getFarValue()); //intilize end while getfarvalue() provide last cordinate
	triangle3df triangle; //create triangle

	line3d<f32> line(start, end);  //create line from start to end
	

	ISceneNode* Hit_Node; // create hit node
	
	//if fire will collide with model then the respective model condition execute  
	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, d_selector, end, triangle, Hit_Node))
	{
		
		score_num++;
		if(array_num <15)
		{}
		else
		{
			array_num=0;
		}

	    if(count_d==3)
		{
			model_play_ninja(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]); //if count=3 then model will move
			count_d=0;
			array_num++;
		}

		else
		{
			count_d++;
		}
	   
	}
	
	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, demon_selector, end, triangle, Hit_Node))
	{
		score_num++;
	    if(array_num <15)
		{}
		else
		{
			array_num=0;
		}
	
		if(count_demon==3)
		{
			model_play_d(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]);
			count_demon=0;
			array_num++;
		}
		else
		{
			count_demon++;
		}
	}

	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, fatso_selector, end, triangle, Hit_Node))
	{
		score_num++;
	    if(array_num <15)
		{}
		else
		{
			array_num=0;
		}

	    if(count_fatso==3)
		{
			model_play_fatso(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]);
			count_fatso=0;
			array_num++;
		}

		else
		{
			count_fatso++;
		}
	}

	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, imp_selector, end, triangle, Hit_Node))
	{
		score_num++;
	    if(array_num <15)
		{}
		else
		{	
			array_num=0;
		}

		if(count_imp==3)
		{
			model_play_i(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]);
			count_imp=0;
			array_num++;
		}
		else
		{
			count_imp++;
		}
	}

	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, warroir_selector, end, triangle, Hit_Node))
	{
		score_num++;
	    if(array_num <15)
		{}
		else
		{
			array_num=0;
		}

		if(count_warroir==3)
		{
			model_play_w(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]);
			count_warroir=0;
			array_num++;
		}
		else
		{
			count_warroir++;
		}
	}


	if(smgr->getSceneCollisionManager()->getCollisionPoint(line, s_selector, end, triangle, Hit_Node))
	{
		score_num++;
	   if(array_num <15)
		{}
		else
		{
			array_num=0;
		}

	   if(count_s==3)
		{
			model_play_s(x_cordinate[array_num],y_cordinate[array_num],z_cordinate[array_num]);
			count_s=0;
			array_num++;
		}
		else
		{
			count_s++;
		}
	}
	

	if (smgr->getSceneCollisionManager()->getCollisionPoint(line, mapSelector, end, triangle, Hit_Node))
	{
		
	}
	else
	{
		}
	
	// create fire ball
	ISceneNode* node = 0;
	
	node = smgr->addBillboardSceneNode(0,dimension2d<f32>(25,25), start); //set dimension of fire from start of camera and 22,22 is dimension through screen 
	node->setMaterialFlag(EMF_LIGHTING, false);//set lighting
	node->setMaterialTexture(0, device->getVideoDriver()->getTexture("Media/fireball.bmp")); //set texture(picture) 
	node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR); //set material texture
	
	f32 length = (f32)(end - start).getLength();//get lenght of fire
	const f32 speed = 3.5f;//speed of firing
	u32 time = (u32)(length / speed);
	
	ISceneNodeAnimator* anim = 0;
	
	anim = smgr->createFlyStraightAnimator(start, end, time);//create animator for animation
	node->addAnimator(anim);
	anim->drop();
	anim = smgr->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();
	
}