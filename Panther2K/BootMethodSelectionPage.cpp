#include "BootMethodSelectionPage.h"
#include "WindowsSetup.h"
#include "QuitingPage.h"

BootMethodSelectionPage::~BootMethodSelectionPage()
{
	free((wchar_t*)text);
}

void BootMethodSelectionPage::Init()
{
	wchar_t* displayName = WindowsSetup::WimImageInfos[WindowsSetup::WimImageIndex - 1].DisplayName;
	int length = lstrlenW(displayName);
	wchar_t* textBuffer = (wchar_t*)safeMalloc(WindowsSetup::GetLogger(), length * sizeof(wchar_t) + 14);
	memcpy(textBuffer, displayName, length * sizeof(wchar_t));
	memcpy(textBuffer + length, L" Setup", 14);
	text = textBuffer;
	statusText = L"  ENTER=Dalej  ESC=Wróć  F3=Zakończ";
}

void BootMethodSelectionPage::Drawer()
{
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	console->SetForegroundColor(WindowsSetup::LightForegroundColor);

	console->SetPosition(3, 4);
	console->Write(L"Wybierz typ swojego komputera.");

	console->SetForegroundColor(WindowsSetup::ForegroundColor);

	console->SetPosition(3, 6);
	console->Write(L"Windows może zostać ustawiony na dwa sposoby jak chodzi o uruchamianie systemu:");

	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	y = console->GetPosition().y + 2;
	console->SetPosition(6, y);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	console->SetForegroundColor(legacy ? WindowsSetup::ForegroundColor : WindowsSetup::BackgroundColor);
	console->SetBackgroundColor(legacy ? WindowsSetup::BackgroundColor : WindowsSetup::ForegroundColor);
	DrawTextLeft(L"UEFI (Zalecane): Nowoczesna metoda uruchamiania systemu. Używa osobnej partycji na której znajdują się pliki które są wymagane aby system Windows się uruchomił. (Wymagane dla systemów Windows 11 i nowszych)", console->GetSize().cx - 18, console->GetPosition().y);

	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	console->SetPosition(6, console->GetPosition().y + 2);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	console->SetForegroundColor(legacy ? WindowsSetup::BackgroundColor : WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(legacy ? WindowsSetup::ForegroundColor : WindowsSetup::BackgroundColor);
	DrawTextLeft(L"Legacy/BIOS: Stara metoda uruchamiania komputera, która używa pierwszy sektor twojego dysku twardego na którym są trzymane dane do załadowania systemu Windows.", console->GetSize().cx - 18, console->GetPosition().y);

	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	DrawTextLeft(L"żyj strzałek LEWO i PRAWO aby wybrać typ komputera.", console->GetSize().cx - 6, console->GetPosition().y + 2);
	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	DrawTextLeft(L"Aby kontynuować z instalacją systemu Windows, naciśnij ENTER.", console->GetSize().cx - 6, console->GetPosition().y + 2);
}

void BootMethodSelectionPage::Redrawer()
{
	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	console->SetPosition(6, y);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	console->SetForegroundColor(legacy ? WindowsSetup::ForegroundColor : WindowsSetup::BackgroundColor);
	console->SetBackgroundColor(legacy ? WindowsSetup::BackgroundColor : WindowsSetup::ForegroundColor);
	DrawTextLeft(L"UEFI (Zalecane): Nowoczesna metoda uruchamiania systemu. Używa osobnej partycji na której znajdują się pliki które są wymagane aby system Windows się uruchomił. (Wymagane dla systemów Windows 11 i nowszych)", console->GetSize().cx - 18, console->GetPosition().y);

	console->SetForegroundColor(WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(WindowsSetup::BackgroundColor);
	console->SetPosition(6, console->GetPosition().y + 2);
	console->Write(WindowsSetup::UseCp437 ? L"\x07" : L"•");
	console->SetForegroundColor(legacy ? WindowsSetup::BackgroundColor : WindowsSetup::ForegroundColor);
	console->SetBackgroundColor(legacy ? WindowsSetup::ForegroundColor : WindowsSetup::BackgroundColor);
	DrawTextLeft(L"Legacy/BIOS: Stara metoda uruchamiania komputera, która używa pierwszy sektor twojego dysku twardego na którym są trzymane dane do załadowania systemu Windows.", console->GetSize().cx - 18, console->GetPosition().y);
}

bool BootMethodSelectionPage::KeyHandler(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
	case VK_DOWN:
		legacy = !legacy;
		Redraw();
		break;
	case VK_ESCAPE:
		WindowsSetup::LoadPhase(2);
		break;
	case VK_RETURN:
		WindowsSetup::GetLogger()->Write(PANTHER_LL_DETAILED, legacy ? L"Using legacy boot." : L"Using UEFI boot.");
		WindowsSetup::UseLegacy = legacy;
		WindowsSetup::LoadPhase(4);
		break;
	case VK_F3:
		AddPopup(new QuitingPage());
		break;
	}
	return true;
}
