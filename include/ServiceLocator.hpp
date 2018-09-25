//
// Created by Patrick RUSSELL on 2018/08/27.
//

#ifndef BOMBERMAN_SERVICELOCATOR_HPP
#define BOMBERMAN_SERVICELOCATOR_HPP

#include "sound/IAudioProvider.hpp"

class ServiceLocator
{
	public:
		ServiceLocator();
		ServiceLocator(ServiceLocator const & src);
		~ServiceLocator();
		static IAudioProvider * getAudio();
		static void RegisterServiceLocator(IAudioProvider *provider);

	private:
		static IAudioProvider * _audioProvider;
};

#endif //BOMBERMAN_SERVICELOCATOR_HPP
