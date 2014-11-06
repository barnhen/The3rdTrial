#pragma once
#include <allegro5\allegro.h>

class Timer
{
    int					timeOffset;
    int					pauseTime;
    bool                paused;

public:
						Timer(void);
    void                start();
    void                pause();
    void                unpause();
    bool                isPaused() const;
    float               getTime() const;
						~Timer(void);
};

/*
	inline : this function will be defined in multiple compilation units, don't worry about it. 
	The linker needs to make sure all compilation units use a single instance of the variable/function.

	So 
    Q: When should I write the keyword 'inline' for a function/method in C++?

	A: Only when you want the function to be defined in a header. More exactly only when the function's 
	definition can show up in multiple compilation units. It's a good idea to define small (as in one liner) 
	functions in the header file as it gives the compiler more information to work with while optimizing your code. 
	It also increases compilation time.
	
    Q: When should I not write the keyword 'inline' for a function/method in C++?

	A: Don't add inline when you think your code will run faster if the compiler inlines it.

    Q: When will the the compiler not know when to make a function/method 'inline'?

	A: Generally the compiler will be able to do this better than you. However, the compiler doesn't have 
	the option to inline code if it doesn't have the function definition. In maximally optimized code usually 
	all private methods are inlined whether you ask for it or not.
*/

inline Timer::Timer()
    : timeOffset(0)
    , pauseTime(0)
    , paused(true)
{ }


inline void Timer::start()
{
    timeOffset = al_get_time();
    pauseTime = 0;
    paused = false;
}

inline void Timer::pause()
{
    if (!paused) {
        pauseTime = al_get_time();
        paused = true;
    }
}

inline void Timer::unpause()
{
    if (paused) {
        timeOffset += al_get_time() - pauseTime;
        paused = false;
    }
}

inline bool Timer::isPaused() const
{
    return paused;
}

inline float Timer::getTime() const
{
    if (!paused) {
        return 0.001f * (al_get_time() - timeOffset);
    } else {
        return 0.001f * pauseTime;
    }
}

