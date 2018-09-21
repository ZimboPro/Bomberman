//
// Created by Patrick RUSSELL on 2018/08/27.
//

#include "ServiceLocator.hpp"

ServiceLocator::ServiceLocator() {}

ServiceLocator::ServiceLocator(ServiceLocator const & src) 
{
	*this = src;
}

ServiceLocator::~ServiceLocator() {}

IAudioProvider * ServiceLocator::getAudio()
{
	return _audioProvider;
}

void ServiceLocator::RegisterServiceLocator(IAudioProvider *provider)
{
	_audioProvider = provider;
}

IAudioProvider * ServiceLocator::_audioProvider = NULL;
