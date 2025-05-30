#ifndef __FLUTTER_NATIVE_LOCAL_H__
#define __FLUTTER_NATIVE_LOCAL_H__

#include "jvxLibHost.h"
#include "flutter_native_host_config.h"

extern "C"
{
#include "flutter_native_api.h"
}

void ffi_get_libhost_pointer(void* opaque_hdl, jvxLibHost*& ll);
void assign_report_functions(callbacks_capi* capi);
bool send_async_dart(report_callback* cbk);
jvxErrorType send_sync_dart(report_callback* cbk);
int ffi_host_allocate_char_array(const std::string& txt, char** txtOnReturn);
void ffi_host_allocate_property_string_list(struct one_property_string_list** ptrRet, const jvxApiStringList& lst);
void ffi_host_allocate_device_capabilities(
	struct device_capabilities** ptrRet,
	const jvxApiString& descror,
	const jvxApiString& description,
	const jvxDeviceCapabilities& caps,
	const jvxComponentIdentification& tpId, 
	const jvxState& stat);
void ffi_host_allocate_selection_option(
	struct selection_option** ptrRet,
	const jvxApiString& descror,
	const jvxApiString& description);

void ffi_host_allocate_val_range(const jvxValueInRange& val, one_property_value_in_range** valArrOnReturn);

void ffi_host_allocate_ss_list(
	struct ss_list** ptrRet,
	jvxSize sz, jvxBool isDevice);

void ffi_host_allocate_component_ident(struct component_ident** ptrRet, const jvxComponentIdentification& cpId);

extern jvxErrorType __last_error;
#define JRE __last_error = JVX_NO_ERROR
#define JSE __last_error = res
;

extern JVX_THREAD_ID mainThreadId;

class jvxRequestCommandHandlerLocal : public CjvxHandleRequestCommands_callbacks
{

public:
	jvxLibHost* backRef = nullptr;

	/**
	 * If the request to run a sequencer step immediately, this callback is triggered.
	 */
	void trigger_immediate_sequencerStep() override;

	/**
	 * For the remaining command requests, the trigger is stored in the request queue and will
	 * be postponed. This way, the request always comes out in a delayed fashion - even if the
	 * request was triggered from within the main thread. */
	void trigger_threadChange_forward(CjvxReportCommandRequest* ptr_to_copy) override;

	/**
	 * If a test request was attached to the queue and all tests runs were completed, the succesful test is
	 * reported to all connected listeners.
	 */
	void run_mainthread_triggerTestChainDone() override;

	/*
	 * This callback is called if the component list of a technology has changed. The technology is passed as cpId.
	 * Typically, we end up here since the the request is delayed into the request event queue.
	 */
	void run_mainthread_updateComponentList(jvxComponentIdentification cpId) override;

	/*
	 * This callback is called if the properties have changed.
	 * Typically, we end up here since the the request is delayed into the request event queue.
	 */
	void run_mainthread_updateProperties(jvxComponentIdentification cpId) override;

	/*
	 * This callback is called if the system state has changed.
	 * Typically, we end up here since the the request is delayed into the request event queue.
	 */
	void run_mainthread_updateSystemStatus() override;

	void run_immediate_rescheduleRequest(const CjvxReportCommandRequest& request) override;

	void report_error(jvxErrorType resError, const CjvxReportCommandRequest& request) override;
};
#endif