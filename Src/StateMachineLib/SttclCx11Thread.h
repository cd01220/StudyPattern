/**
 * @file SttclCx11Thread.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STTCLCX11THREAD_H_
#define STTCLCX11THREAD_H_

#if defined(STTCL_CX11_THREADS) || defined(STTCL_CX11_IMPL)
#include <thread>
#include "../include/SttclTime.h"

namespace sttcl
{
namespace internal
{
namespace cx11_impl
{
/**
 * The C++ 11 standard default implementation for sttcl::SttclThread<>.
 */
class SttclCx11Thread
{
public:
	typedef std::thread ThreadNativeType;

	typedef void* (*ThreadMethodPtr)(void*);

	SttclCx11Thread(ThreadMethodPtr argThreadMethod)
        : threadMethod(argThreadMethod), thread()
    {
	    detach();
    }

	virtual ~SttclCx11Thread()
    {
	    if(thread.joinable())
	    {
		    thread.join();
	    }
    }

	bool run(void* args)
    {
	    thread = std::thread(*threadMethod,args);
	    return true;
    }

	void join()
    {
	    if(thread.joinable())
	    {
		    thread.join();
	    }
    }

	void detach()
    {
	    if(thread.joinable())
	    {
		    thread.detach();
	    }
    }

    static bool isSelf(const SttclCx11Thread& otherThread)
    {
	    return std::this_thread::get_id() == otherThread.thread.get_id();
    }

    static void sleep(const TimeDuration<>& duration)
    {
        std::this_thread::sleep_for(duration.getNativeValue());
    }

private:
	ThreadMethodPtr threadMethod;
	ThreadNativeType thread;

};
}
}
}
#endif
#endif /* STTCLCX11THREAD_H_ */
