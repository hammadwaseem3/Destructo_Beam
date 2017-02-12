#ifndef HEALTH_H
#define HEALTH_H


class health //class for health
{
	private :
		int p_health ; 
	
	public :
		
		health () : p_health(5) {} 
		
		void setHealth ();

		void changehealth();
		
} ;

#endif