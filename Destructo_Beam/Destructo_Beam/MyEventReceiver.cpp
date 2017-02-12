#include "MyEventReceiver.h"


 bool MyEventReceiver::OnEvent(const SEvent& event)
{
		
		if (event.EventType == EET_GUI_EVENT)  //if receive an gui event
		{
			s32 id = event.GUIEvent.Caller->getID();   //get id (we set the id for button)
			switch(event.GUIEvent.EventType)            //event receive
			{
				case EGET_BUTTON_CLICKED:               //if event type is muse click
				switch(id)
			
				{
			
					case 1:
					{
					
						m1.setMap();
						m1.exeMap();
		
						while(m1.d())
						{
		
							m1.playMap();
						}

						m1.drop();
					}

					return true;
			
					case 2:
				
					{
						Context.device->closeDevice();
					}
					
					return true;
			   
				
					default:

						return false;
				}
						break;
			}
		}

		return false;
}