//
// Created by Patrick RUSSELL on 2018/08/27.
//

#include "ServiceLocator.hpp"

IAudioProvider * ServiceLocator::getAudio()
{
	return _audioProvider;
}

void ServiceLocator::RegisterServiceLocator(IAudioProvider *provider)
{
	_audioProvider = provider;
}

IAudioProvider * ServiceLocator::_audioProvider = NULL;
