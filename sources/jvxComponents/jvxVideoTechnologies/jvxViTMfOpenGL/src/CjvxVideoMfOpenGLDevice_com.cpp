#include "CjvxVideoMfOpenGLDevice.h"

#include <shlwapi.h> // QITAB and friends
#include <objbase.h> // IID_PPV_ARGS and friends
//#include <dshow.h> // IAMVideoProcAmp and friends

// ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##

// IUnknown methods
STDMETHODIMP 
CjvxVideoMfOpenGLDevice::QueryInterface(REFIID aRiid, void** aPpv)
{
	static const QITAB qit[] =
	{
		QITABENT(CjvxVideoMfOpenGLDevice, IMFSourceReaderCallback),
		{ 0 },
	};
	return QISearch(this, qit, aRiid, aPpv);
}

STDMETHODIMP_(ULONG) 
CjvxVideoMfOpenGLDevice::AddRef()
{
	return InterlockedIncrement(&mRefCount);
}

STDMETHODIMP_(ULONG) 
CjvxVideoMfOpenGLDevice::Release()
{
	ULONG count = InterlockedDecrement(&mRefCount);
	if (count == 0)
	{
		delete this;
	}
	// For thread safety, return a temporary variable.
	return count;
}

// IMFSourceReaderCallback methods
STDMETHODIMP 
CjvxVideoMfOpenGLDevice::OnReadSample(
	HRESULT aStatus,
	DWORD aStreamIndex,
	DWORD aStreamFlags,
	LONGLONG aTimestamp,
	IMFSample *aSample
)
{
	HRESULT hr = S_OK;
	IMFMediaBuffer *mediabuffer = NULL;
	jvxErrorType resL = JVX_NO_ERROR;

	jvxTick stoptt;
	jvxTick deltat;
	if (FAILED(aStatus))
	{
		// Bug workaround: some resolutions may just return error.
		// http://stackoverflow.com/questions/22788043/imfsourcereader-giving-error-0x80070491-for-some-resolutions
		// we fix by marking the resolution bad and retrying, which should use the next best match.
		std::cout << "Buffer switch callback failed!" << std::endl;
		/*
		mRedoFromStart = 1;
		if (mBadIndices == mMaxBadIndices)
		{
			unsigned int *t = new unsigned int[mMaxBadIndices * 2];
			memcpy(t, mBadIndex, mMaxBadIndices * sizeof(unsigned int));
			delete[] mBadIndex;
			mBadIndex = t;
			mMaxBadIndices *= 2;
		}
		mBadIndex[mBadIndices] = mUsedIndex;
		mBadIndices++;*/
		return aStatus;
	}
	else
	{
		//EnterCriticalSection(&mCritsec);
		if (aSample)
		{
			jvxTick startt = JVX_GET_TICKCOUNT_US_GET_CURRENT(&tStamp);
			jvxErrorType res = JVX_NO_ERROR;
			if (runtime.lastTime > 0)
			{
				runtime.avrgT = runtime.avrgT * (ALPHA)+(1 - ALPHA) * (startt - runtime.lastTime);
			}
			runtime.lastTime = startt;
			CjvxVideoDevice_genpcg::rt_info_vd.detected_rate.value = 1000000.0 / runtime.avrgT;

			// In this function, we get the desired buffer target index
			res = _common_set_ocon.theData_out.con_link.connect_to->process_start_icon();
			assert(res == JVX_NO_ERROR);

			IMF2DBuffer     *m2DBuffer = NULL;
			// Get the video frame buffer from the sample.

			hr = aSample->GetBufferByIndex(0, &mediabuffer);
			if (mediabuffer)
			{
				// Access buffer

				// Query for the 2-D buffer interface. 
				mediabuffer->QueryInterface(IID_PPV_ARGS(&m2DBuffer));
				if (m2DBuffer)
				{
					runtime.numFrames++;
					//JVX_LOCK_MUTEX(safeAccess);
					//jvxSize bufIdx = (runtime.bufIdx + runtime.bufFHeight) % runtime.numBufs;
					//jvxState stat = runtime.fldBufStat[bufIdx];
					//JVX_UNLOCK_MUTEX(safeAccess);

					jvxSize i;
					BYTE* src = NULL;
					LONG stride = 0;
					//std::cout << "Start capture buffer " << theData.pipeline.idx_stage << std::endl;
					jvxByte* dest = (jvxByte*)_common_set_ocon.theData_out.con_data.buffers[
						*_common_set_ocon.theData_out.con_pipeline.idx_stage_ptr][0];
						m2DBuffer->Lock2D(&src, &stride);

						// If source is browsed from toe to the head, we do the same for the
						// texture target buffer
						if (stride < 0)
						{
							dest += (_common_set_ocon.theData_out.con_params.segmentation.y - 1)* runtime.szLine;
						}

						// This copies the lines in target buffer: from 
						// - .. higher lines to lower lines in target buffer
						// - .. from end to beginning in src buffer
						for (i = 0; i < _common_set_ocon.theData_out.con_params.segmentation.y; i++)
						{
							memcpy(dest, src, runtime.szLine);
							src += stride;
							dest -= runtime.szLine;
						}
						m2DBuffer->Unlock2D();
						//std::cout << "Stop capture buffer " << theData.pipeline.idx_stage << std::endl;

						//JVX_LOCK_MUTEX(safeAccess);
						//runtime.fldBufStat[bufIdx] = JVX_STATE_ACTIVE;
						//runtime.bufFHeight++;
						//JVX_UNLOCK_MUTEX(safeAccess);
						m2DBuffer->Release();
				}
				else
				{
					BYTE* src = NULL;
					LONG stride = 0;
					DWORD cbMaxLength = 0;
					DWORD cbCurrentLength = 0;
					mediabuffer->Lock(&src, &cbMaxLength, &cbCurrentLength);

					if (src)
					{
						jvxByte* dest = (jvxByte*)_common_set_ocon.theData_out.con_data.buffers[
							*_common_set_ocon.theData_out.con_pipeline.idx_stage_ptr][0];
						jvxSize i;
						for (i = 0; i < _common_set_ocon.theData_out.con_params.segmentation.y; i++)
						{
							memcpy(dest, src, runtime.szLine);
							src += runtime.szLine;
							dest += runtime.szLine;
						}
						//runtime.stride
					}
					mediabuffer->Unlock();
					//assert(0);
				}


				mediabuffer->Release();

				// Process buffer
				res = _common_set_ocon.theData_out.con_link.connect_to->process_buffers_icon();
				assert(res == JVX_NO_ERROR);

				// Processing complete
				res = _common_set_ocon.theData_out.con_link.connect_to->process_stop_icon();
				assert(res == JVX_NO_ERROR);
			}
			else
			{
				CjvxVideoDevice::rt_info_vd.number_lost_frames.value++;
			}
			stoptt = JVX_GET_TICKCOUNT_US_GET_CURRENT(&tStamp);
			deltat = stoptt - startt;
			CjvxVideoDevice::rt_info_vd.delta_t_copy.value = CjvxVideoDevice::rt_info_vd.delta_t_copy.value * ALPHA +
				(1 - ALPHA) * deltat;
		}
	}

	if( runtime.streamState == JVX_STATE_PROCESSING)
	{
		// Request the next frame.
		hr = readPtr->ReadSample(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			0,
			NULL,   // actual
			NULL,   // flags
			NULL,   // timestamp
			NULL    // sample
		);
	}
	else
	{
		if (runtime.streamState == JVX_STATE_COMPLETE)
		{
			// We need to stop here
			runtime.streamState = JVX_STATE_PREPARED;
		}
		else
		{
			assert(0);
		}
	}

	return hr;
}

STDMETHODIMP 
CjvxVideoMfOpenGLDevice::OnEvent(DWORD, IMFMediaEvent *)
{
	return S_OK;
}

STDMETHODIMP 
CjvxVideoMfOpenGLDevice::OnFlush(DWORD)
{
	return S_OK;
}