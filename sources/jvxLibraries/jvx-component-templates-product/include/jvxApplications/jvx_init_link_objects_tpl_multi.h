#ifdef JVX_USE_ASIO
#include "jvxAuTAsio.h"
#endif

#ifdef JVX_OS_LINUX
#include "jvxAuTAlsa.h"
#endif

#ifdef JVX_OS_MACOSX
#include "jvxAuTCoreAudio.h"
#endif

#ifdef JVX_USE_PORTAUDIO
#include "jvxAuTPortAudio.h"
#endif

#ifdef JVX_USE_WASAPI
#include "jvxAuTWindows.h"
#endif

#ifdef JVX_HOST_USE_REMOTE_CALL
#include "jvxTRemoteCall.h"
#endif

#ifdef JVX_HOST_USE_CONNECTION
#include "jvxTSocket.h"

#ifdef JVX_RS232_ACTIVE
#ifdef JVX_OS_WINDOWS
#include "jvxTRs232Win32.h"
#endif
#ifdef JVX_OS_Linux
#include "jvxTRs232Glnx.h"
#endif
#endif

#endif

extern "C"
{
	jvxErrorType jvx_access_link_objects(
		jvxInitObject_tp* funcInit,
		jvxTerminateObject_tp* funcTerm, jvxApiString* adescr,
		jvxComponentType tp, jvxSize id)
	{
		jvxSize cnt = 0;

		switch (tp)
		{
		case JVX_COMPONENT_AUDIO_TECHNOLOGY:

#ifdef JVX_USE_PORTAUDIO
			if (id == cnt)
			{
				adescr->assign("PortAudio Audio");
				*funcInit = jvxAuTPortAudio_init;
				*funcTerm = jvxAuTPortAudio_terminate;
				return(JVX_NO_ERROR);
			}
			cnt++;
#endif
#if defined JVX_USE_WASAPI

			if (id == cnt)
			{
				adescr->assign("Windows Audio");
				*funcInit = jvxAuTWindows_init;
				*funcTerm = jvxAuTWindows_terminate;
				return(JVX_NO_ERROR);
			}
			cnt++;

#elif defined JVX_USE_ALSA
			if (id == cnt)
			{
				adescr->assign("Alsa Audio");
				*funcInit = jvxAuTAlsa_init;
				*funcTerm = jvxAuTAlsa_terminate;
				return(JVX_NO_ERROR);
			}
			cnt++;
#elif defined JVX_USE_COREAUDIO

			if (id == cnt)
			{
				adescr->assign("Core Audio");
				*funcInit = jvxAuTCoreAudio_init;
				*funcTerm = jvxAuTCoreAudio_terminate;
				return(JVX_NO_ERROR);
			}
			cnt++;
#endif

#if defined JVX_USE_ASIO
			if (id == cnt)
			{
				adescr->assign("Asio Audio");
				*funcInit = jvxAuTAsio_init;
				*funcTerm = jvxAuTAsio_terminate;
				return(JVX_NO_ERROR);
			}
			cnt++;
#endif

#ifdef JVX_ADDITIONAL_TECHNOLOGIES
			JVX_ADDITIONAL_TECHNOLOGIES
#endif

			break;

#ifdef JVX_ALL_AUDIONODE_CASES
		case JVX_COMPONENT_AUDIO_NODE:
			switch (id)
			{

			JVX_ALL_AUDIONODE_CASES

			default:
				break;
			}
			break;
#endif

#ifdef JVX_ALL_SPNODE_CASES
		case JVX_COMPONENT_SIGNAL_PROCESSING_NODE:
			switch (id)
			{

				JVX_ALL_SPNODE_CASES

			default:
				break;
			}
			break;
#endif

#ifdef JVX_HOST_USE_REMOTE_CALL

		case JVX_COMPONENT_REMOTE_CALL:
			switch (id)
			{
			case 0:
				adescr->assign("Remote Call");
				*funcInit = jvxTRemoteCall_init;
				*funcTerm = jvxTRemoteCall_terminate;
				return(JVX_NO_ERROR);

			default:
				break;
			}
			break;

#endif

#ifdef JVX_HOST_USE_CONNECTION
		case JVX_COMPONENT_CONNECTION:
			switch (id)
			{
			case 0:
				adescr->assign("Socket");
				*funcInit = jvxTSocket_init;
				*funcTerm = jvxTSocket_terminate;
				return(JVX_NO_ERROR);

#ifdef JVX_OS_WINDOWS

			case 1:
				adescr->assign("Rs232");
				*funcInit = jvxTRs232Win32_init;
				*funcTerm = jvxTRs232Win32_terminate;
				return(JVX_NO_ERROR);

#endif
			default:
				break;
			}
			break;
#endif

#ifdef JVX_ALLOTHER_CLASSES
			JVX_ALLOTHER_CLASSES
#endif
		default:
			break;
		}
		return(JVX_ERROR_ELEMENT_NOT_FOUND);
	}
}


