/**
 * @file SttclTime.h
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

#ifndef STTCLTIME_H_
#define STTCLTIME_H_

#ifndef STTCL_DEFAULT_TIMEDURATIONIMPL
#if defined(STTCL_POSIX_TIME)  || defined(STTCL_POSIX_IMPL)
#include "SttclPosixTime.h"
#define STTCL_DEFAULT_TIMEDURATIONIMPL sttcl::internal::posix_impl::SttclPosixTimeDuration
#elif defined(STTCL_BOOST_TIME) || defined(STTCL_BOOST_IMPL)
#include "SttclBoostTime.h"
#define STTCL_DEFAULT_TIMEDURATIONIMPL sttcl::internal::boost_impl::SttclBoostTimeDuration
#elif defined(STTCL_CX11_TIME) || defined(STTCL_CX11_IMPL)
#include "SttclCx11Time.h"
#define STTCL_DEFAULT_TIMEDURATIONIMPL sttcl::internal::cx11_impl::SttclCx11TimeDuration
#endif

#ifndef STTCL_DEFAULT_TIMEDURATIONIMPL
#error "You need to define a default time duration implementation for sttcl"
#endif
#endif

namespace sttcl
{

/**
 * Adapter class for a (OS-)specific "real"-time duration representation implementation.
 * @tparam Implementation Selects a (OS-)specific "real"-time duration representation implementation.
 *
 * @todo Implement a static interface check for the Impl class.
 */
template<class Implementation = STTCL_DEFAULT_TIMEDURATIONIMPL>
class TimeDuration
: public Implementation
{
public:
	/**
	 * The class type of the native "real"-time duration representation.
	 */
	typedef typename Implementation::NativeTimeDuration NativeTimeDuration;

	/**
	 * Represents a zero time duration.
	 */
	static const TimeDuration<Implementation> Zero;

	/**
	 * Constructor for class TimeDuration.
	 * @param argHours The hours represented in this instance.
	 * @param argMinutes The minutes represented in this instance.
	 * @param argSeconds  The seconds represented in this instance.
	 * @param argMilliSeconds The milliseconds represented in this instance.
	 * @param argMicroSeconds The microseconds represented in this instance.
	 * @param argNanoSeconds The nanoseconds represented in this instance.
	 */
	TimeDuration(unsigned int argHours = 0, unsigned int argMinutes = 0, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: Implementation(argHours,argMinutes,argSeconds,argMilliSeconds,argMicroSeconds,argNanoSeconds)
	{
	}

	/**
	 * Copy constructor for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 */
	TimeDuration(const TimeDuration<Implementation>& rhs)
	: Implementation(static_cast<const Implementation&>(rhs))
	{
	}
	/**
	 * Constructor for class TimeDuration.
	 * @param nativeTimeDuration An instance of the NativeTimeDuration value.
	 */
	TimeDuration(const NativeTimeDuration& nativeTimeDuration)
	: Implementation(nativeTimeDuration)
	{
	}
	/**
	 * Destructor for class TimeDuration.
	 */
	~TimeDuration()
	{
	}

	/**
	 * Assignment operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the assigned TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Assignment operator for class TimeDuration.
	 * @param nativeTimeDuration An instance of the NativeTimeDuration value.
	 * @return A reference to the assigned TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator=(const NativeTimeDuration& nativeTimeDuration)
	{
		Implementation::operator=(static_cast<const Implementation&>(nativeTimeDuration));
		return *this;
	}

	/**
	 * Equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration equals this instance, \c false otherwise.
	 */
	bool operator==(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator==(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Inequality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration doesn't equal this instance, \c false otherwise.
	 */
	bool operator!=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator!=(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Less comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is less than this instance, \c false otherwise.
	 */
	bool operator<(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Less or equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is less than or equals this instance, \c false otherwise.
	 */
	bool operator<=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<=(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Greater comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is greater than this instance, \c false otherwise.
	 */
	bool operator>(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Greater or equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is greater than or equals this instance, \c false otherwise.
	 */
	bool operator>=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>=(static_cast<const Implementation&>(rhs));
	}

	/**
	 * Adds the \em rhs time duration to this instance.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator+=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator+=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Substracts the \em rhs time duration from this instance.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator-=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator-=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Multiplies the \em time duration from of this instance with \em factor.
	 * @param factor The multiplication factor.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator*=(int factor)
	{
		Implementation::operator*=(factor);
		return *this;
	}

	/**
	 * Divides the \em time duration from of this instance by \em divider.
	 * @param divider The divider.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator/=(int divider)
	{
		Implementation::operator/=(divider);
		return *this;
	}

	/**
	 * Gets the hours represented in this instance.
	 */
	long hours() const
	{
		return Implementation::hours();
	}
	/**
	 * Gets the minutes represented in this instance.
	 */
	long minutes() const
	{
		return Implementation::minutes();
	}
	/**
	 * Gets the seconds represented in this instance.
	 */
	long seconds() const
	{
		return Implementation::seconds();
	}
	/**
	 * Gets the milliseconds represented in this instance.
	 */
	long milliseconds() const
	{
		return Implementation::milliseconds();
	}
	/**
	 * Gets the microseconds represented in this instance.
	 */
	long microseconds() const
	{
		return Implementation::microseconds();
	}
	/**
	 * Gets the nanoseconds represented in this instance.
	 */
	long nanoseconds() const
	{
		return Implementation::nanoseconds();
	}

	/**
	 * Sets the hours represented in this instance.
	 */
	void hours(int newHours)
	{
		Implementation::hours(newHours);
	}
	/**
	 * Sets the minutes represented in this instance.
	 */
	void minutes(int newMinutes)
	{
		Implementation::minutes(newMinutes);
	}
	/**
	 * Sets the seconds represented in this instance.
	 */
	void seconds(int newSeconds)
	{
		Implementation::seconds(newSeconds);
	}

	/**
	 * @todo Implement methods to set milliseconds, microseconds and nanoseconds in a consistent way with the getters.
	 */
	/**
	 * Sets the milliseconds represented in this instance.
	 */
	/*
	void milliseconds(int newMilliSeconds)
	{
		Implementation::milliseconds(newMilliSeconds);
	}
	*/
	/**
	 * Sets the microseconds represented in this instance.
	 */
	/*
	void microseconds(int newMicroSeconds)
	{
		Implementation::microseconds(newMicroSeconds);
	}
	*/
	/**
	 * Sets the nanoseconds represented in this instance.
	 */
	/*
	void nanoseconds(long newNanoSeconds)
	{
		Implementation::nanoseconds(newNanoSeconds);
	}
	*/

	/**
	 * Gets the native "real"-time duration representation.
	 * @return
	 */
	const NativeTimeDuration& getNativeValue() const
	{
		return Implementation::getNativeValue();
	}
};


}

template<class Implementation>
static sttcl::TimeDuration<Implementation> operator+(const sttcl::TimeDuration<Implementation>& op1, const sttcl::TimeDuration<Implementation>& op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result += op2;
}

template<class Implementation>
static sttcl::TimeDuration<Implementation> operator-(const sttcl::TimeDuration<Implementation>& op1, const sttcl::TimeDuration<Implementation>& op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result -= op2;
}
template<class Implementation>
static sttcl::TimeDuration<Implementation> operator*(const sttcl::TimeDuration<Implementation>& op1, int op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result *= op2;
}
template<class Implementation>
static sttcl::TimeDuration<Implementation> operator/(const sttcl::TimeDuration<Implementation>& op1, int op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result /= op2;
}

template<class Implementation>
const sttcl::TimeDuration<Implementation> sttcl::TimeDuration<Implementation>::Zero = sttcl::TimeDuration<Implementation>();
#endif /* STTCLTIME_H_ */
