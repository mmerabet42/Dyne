#include "Application.hpp"
#include "Audio.hpp"

void dn::Application::addAudio(dn::Audio *p_audio)
{
	if (dn::Application::_running)
		p_audio->create();
	else
		dn::Application::_audios.push_back(p_audio);
}

void dn::Application::createAudios()
{
	for (size_t i = 0; i < dn::Application::_audios.size(); ++i)
		dn::Application::_audios[i]->create();
	dn::Application::_audios.clear();
}
