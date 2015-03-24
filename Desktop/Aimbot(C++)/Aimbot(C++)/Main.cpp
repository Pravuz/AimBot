
#include "Main.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AimbotC::Main form;
	Application::Run(%form); 4
	;
}

