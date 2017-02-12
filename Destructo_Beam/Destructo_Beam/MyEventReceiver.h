#include <irrlicht.h>
#include "Map.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif


struct ApContext
{
	IrrlichtDevice *device;
	
};


class MyEventReceiver : public IEventReceiver  //responsible for every event in gui
{
	private:
		ApContext & Context;
		Map m1;

	public:
		MyEventReceiver(ApContext & context) : Context(context) { } //constructor
		bool OnEvent(const SEvent& event);
	
};