#include "aplikacja.h"



//[System::STAThreadAttribute]
int main(array<System::String^>^ args) {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	Multifiltr::aplikacja form;
	System::Windows::Forms::Application::Run(% form);
	return 0;
}