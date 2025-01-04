#include "WelcomePage.h"
#include "QuitingPage.h"
#include "WindowsSetup.h"
#include "ImageSelectionPage.h"

void WelcomePage::Init()
{
	text = L"Instalator systemu Windows XP Professional";
	statusText = L"  ENTER=Dalej  R=Napraw  F3=Zakończ";
}

void WelcomePage::Drawer()
{
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	console->SetForegroundColor(WindowsSetup::LightForegroundColor);
	console->SetPosition(3, 4);
	console->Write(L"Zapraszamy do programu instalacyjnego.");

	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	DrawTextLeft(L"Ta część pracy Instalatora przygotuje system Microsoft(R) Windows(R) XP do uruchomienia na tym komputerze.", console->GetSize().cx - 6, 6);
	
	console->SetPosition(6, console->GetPosition().y + 2);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	DrawTextLeft(L"Aby rozpocząć instalację systemu Windows XP, naciśnij klawisz ENTER.", console->GetSize().cx - 18, console->GetPosition().y);

	console->SetPosition(6, console->GetPosition().y + 2);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	DrawTextLeft(L"Aby naprawić istniejącą instalację systemu Windows XP przy użyciu Konsoli odzyskiwania, naciśnij klawisz R.", console->GetSize().cx - 18, console->GetPosition().y);

	console->SetPosition(6, console->GetPosition().y + 2);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	DrawTextLeft(L"Aby zakończyć pracę Instalatora bez instalowania systemu Windows XP, naciśnij klawisz F3.", console->GetSize().cx - 18, console->GetPosition().y);
}

void WelcomePage::Redrawer()
{
}

bool WelcomePage::KeyHandler(WPARAM wParam)
{
	switch (wParam) 
	{
	case VK_RETURN:
		statusText = L"  Czekaj...";
		Draw();
		WindowsSetup::LoadPhase(2);
		break;
	case (WPARAM)'R':
		break;
	case VK_F3:
		AddPopup(new QuitingPage());
		break;
	}
	return true;
}
