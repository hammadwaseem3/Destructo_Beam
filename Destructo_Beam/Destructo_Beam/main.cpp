#include"Map.h"
#include "health.h"
#include "MyEventReceiver.h"


int main()
{

	IrrlichtDevice * device = createDevice(EDT_OPENGL, dimension2d<u32>(1500, 880),16,true);  //it creates a device 
	if (device == 0)
	{
		return 1; 
	}

	IVideoDriver* driver1 = device->getVideoDriver();   //video driver is included responsible for display
	IVideoDriver* dr = device->getVideoDriver();
	
	ISceneManager* smgr1 = device->getSceneManager();  //scenemanager responsible for every scene
	
	IGUIEnvironment* env = device->getGUIEnvironment();   //get gui envoriment
	IGUISkin* skin = env->getSkin();  // get skin for gui
	IGUIFont* font = env->getFont("Media/fonthaettenschweiler.bmp");  // get font
	

	if (font)
	{
		skin->setFont(font); // set font in skin of gui means what ever print in gui then font used is this
	}

	
	IGUITabControl* tabctrl = env->addTabControl(rect<int>(260,10,512-10,384-10),  0 , true, true);  //display a tab in gui
	
	IGUITab* optTab = tabctrl->addTab(L"Destructo Beam");  //put tab name
	
	const wchar_t* text2 = L"This game is develop by AH production.The developer of this game are hammad waseem and ali shah meghani.This was their CP project\n"; //save text
	
	env->addStaticText(text2, rect<int>(10, 10, 230, 320),true, true, optTab); //add text
	
	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP); //if font is not selected then it use defaul font
	
	env->addButton(rect<s32>(300,240,460,272), 0, 2, L"Quit", L"Exits Program"); // put button name start game
	
	env->addButton(rect<s32>(300,300,460,332), 0, 1,L"Start Game"); // put button name start game
	
	smgr1->addCameraSceneNode(0, vector3df(45,0,0), vector3df(0,0,10)); //add camera
    
	ITexture* CS = driver1->getTexture("Media/cs.jpg"); //put picture
	
	
	ApContext context; //create object
	context.device = device; //save the current device in the device of object 

	MyEventReceiver receiver(context); //it receivce every event
	
	device->setEventReceiver(&receiver); //set event receive above 
	
	env->addImage(driver1->getTexture("Media/Fast.jpg"),position2d<int>(10,10)); //add image

	ITexture* title = dr->getTexture("Media/title2.jpg"); //add image
	ITexture* loading = dr->getTexture("Media/loading2.jpg"); //add image
	
		
	
	int count=0;
	
	while(device->run())
	{
		if(count <500)
		{
			dr->draw2DImage(title, position2d<s32>(0, 0),rect<s32>(0, 0,1500, 1150), 0,SColor(255, 255, 255, 255),true);
			count++;
			dr->endScene();//end scene
		}

		else
		{
			if(count < 1000)
			{
				dr->draw2DImage(loading, position2d<s32>(0, 0),rect<s32>(0, 0,1500, 1150), 0,SColor(255, 255, 255, 255),true);
				count++;
				dr->endScene();
				count++;
			}

			else
			{
				driver1->beginScene(true, true, SColor(255,0,0,0));
				
				if (CS)
				{
					driver1->draw2DImage(CS,
					position2d<int>(0,0));
				}

			env->drawAll();    //draw every thing we edit in gui
			smgr1->drawAll();   //draw every thing we edit in scenemanager
			driver1->endScene();  //end scene
	
			}
		}
	}
	
	device->drop();

	return 0;
}