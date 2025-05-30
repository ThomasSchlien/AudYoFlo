#ifndef __CJVXSINGLECONNECTOR_REPORT_H__
#define __CJVXSINGLECONNECTOR_REPORT_H__

template <class T>
JVX_INTERFACE CjvxSingleConnector_report
{
public:
	virtual ~CjvxSingleConnector_report() {};

	virtual jvxErrorType report_selected_connector(T* iconn) = 0;
	virtual void request_unique_id_start(T* iconn, jvxSize* uId) = 0;
	virtual jvxErrorType report_started_connector(T* iconn) = 0;

	virtual jvxErrorType report_stopped_connector(T* iconn) = 0;
	virtual void release_unique_id_stop(T* iconn, jvxSize uId) = 0;
	virtual jvxErrorType report_unselected_connector(T* iconn) = 0;

	virtual void report_process_buffers(T* iconn, jvxHandle** bufferPtrs, const jvxLinkDataDescriptor_con_params& params) = 0;
};

#endif
