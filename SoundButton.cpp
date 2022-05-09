#include "SoundButton.h"
#include "Application.h"
#include "Texture.h"

void SoundButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);

	if(Application::GetInstance()->m_appSoundState == SoundState::OFF) this->SetTexture(Resources::GetInstance()->GetTexture(("Images/Buttons/Sound_Off.png")));

}

void SoundButton::OnRender()
{
	Button::OnRender();
}

void SoundButton::OnClick()
{
		switch (Application::GetInstance()->m_appSoundState)
		{
		case SoundState::ON:

			Application::GetInstance()->m_appSoundState = SoundState::OFF;
			this->SetTexture(Resources::GetInstance()->GetTexture("Images/Buttons/Sound_Off.png"));

			break;

		case SoundState::OFF:

			Application::GetInstance()->m_appSoundState = SoundState::ON;
			this->SetTexture(Resources::GetInstance()->GetTexture(("Images/Buttons/Sound_On.png")));


			break;
		}
	
		Button::OnClick();
}

