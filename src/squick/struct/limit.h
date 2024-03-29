#ifndef SQUICK_LIMIT_H
#define SQUICK_LIMIT_H

#pragma pack(push,1)

#define SQUICK_NAME_MAXLEN          32              
#define SQUICK_BROAD_MAXLEN         64             
#define SQUICK_PATH_MAXLEN          128            
#define SQUICK_ACCOUNT_MAXROLE      4               
#define SQUICK_ROLE_MAXPKG          150             
#define SQUICK_ROLE_DEFAULTPKG      60              

#define SQUICK_VIEWGRID_UNIT        200             
#define SQUICK_VIEWSIZE_MAXLEN      9               

//#define SQUICK_SCENE_LEFTLENPOS       -32000      
//#define SQUICK_SCENE_RIGHTPOS     32000           

//#define SQUICK_MAX_ONLINE         3000            


#ifdef SQUICK_DEBUG_MODE

#if SQUICK_PLATFORM == SQUICK_PLATFORM_WIN

#elif SQUICK_PLATFORM == SQUICK_PLATFORM_LINUX || SQUICK_PLATFORM == SQUICK_PLATFORM_ANDROID

#elif SQUICK_PLATFORM == SQUICK_PLATFORM_APPLE || SQUICK_PLATFORM == SQUICK_PLATFORM_APPLE_IOS
#endif

#else

#if SQUICK_PLATFORM == SQUICK_PLATFORM_WIN

#elif SQUICK_PLATFORM == SQUICK_PLATFORM_LINUX || SQUICK_PLATFORM == SQUICK_PLATFORM_ANDROID

#elif SQUICK_PLATFORM == SQUICK_PLATFORM_APPLE || SQUICK_PLATFORM == SQUICK_PLATFORM_APPLE_IOS
#endif

#endif

class _NFExport DoNothing
{
public:
	void DonOTHING()
	{

	}
};


#pragma pack(pop)



#endif