#pragma once
#include "Aimbot_Serial.h"
namespace AimbotC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			findPorts();
			AimBot_Serial desktop_Serial(serialPort, 115200);
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^  serialPort;
	private: System::Windows::Forms::ComboBox^  cboPorts;
	private: System::Windows::Forms::Button^  btnClose;

	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::TextBox^  txtRecived;


	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  lblPorts;
	private: System::Windows::Forms::Label^  lblStatus;
	private: System::Windows::Forms::Label^  lblRecived;


	protected:

	protected:
	private: System::ComponentModel::IContainer^  components;

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			this->cboPorts = (gcnew System::Windows::Forms::ComboBox());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->txtRecived = (gcnew System::Windows::Forms::TextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->lblPorts = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblRecived = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// serialPort
			// 
			this->serialPort->BaudRate = 115200;
			this->serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Main::serialPort_DataRecived);
			// 
			// cboPorts
			// 
			this->cboPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboPorts->FormattingEnabled = true;
			this->cboPorts->Location = System::Drawing::Point(12, 23);
			this->cboPorts->Name = L"cboPorts";
			this->cboPorts->Size = System::Drawing::Size(157, 21);
			this->cboPorts->TabIndex = 0;
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(93, 50);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(75, 48);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = L"Close Port";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &Main::btnClose_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 50);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 48);
			this->btnOpen->TabIndex = 2;
			this->btnOpen->Text = L"Open Port";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Main::btnOpen_Click);
			// 
			// txtRecived
			// 
			this->txtRecived->Location = System::Drawing::Point(175, 23);
			this->txtRecived->Multiline = true;
			this->txtRecived->Name = L"txtRecived";
			this->txtRecived->ReadOnly = true;
			this->txtRecived->Size = System::Drawing::Size(100, 300);
			this->txtRecived->TabIndex = 3;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(-1, 329);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(284, 23);
			this->progressBar1->TabIndex = 4;
			// 
			// lblPorts
			// 
			this->lblPorts->AutoSize = true;
			this->lblPorts->Location = System::Drawing::Point(12, 7);
			this->lblPorts->Name = L"lblPorts";
			this->lblPorts->Size = System::Drawing::Size(55, 13);
			this->lblPorts->TabIndex = 5;
			this->lblPorts->Text = L"Com Ports";
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(12, 313);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(79, 13);
			this->lblStatus->TabIndex = 6;
			this->lblStatus->Text = L"Not Connected";
			// 
			// lblRecived
			// 
			this->lblRecived->AutoSize = true;
			this->lblRecived->Location = System::Drawing::Point(187, 7);
			this->lblRecived->Name = L"lblRecived";
			this->lblRecived->Size = System::Drawing::Size(73, 13);
			this->lblRecived->TabIndex = 7;
			this->lblRecived->Text = L"Data Recived";
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(281, 359);
			this->Controls->Add(this->lblRecived);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblPorts);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->txtRecived);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->cboPorts);
			this->Name = L"Main";
			this->Text = L"Main";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// find availeble ports
	delegate void SetTextBoxDtype(System::String ^);
		
	private: void findPorts(){
				 array<Object^>^ objectArray = serialPort->GetPortNames();

				 this->cboPorts->Items->AddRange(objectArray);
				 
	}

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->txtRecived->Clear();
				 if (this->cboPorts->Text == String::Empty)
					 MessageBox::Show("No Port Selected", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
				 else {
					 try{
						 // make sure port is not open
						 if (!this->serialPort->IsOpen){
							 //Set the name of the port from the combobox
							 this->serialPort->PortName = this->cboPorts->Text;
							 //Set the baud-rate of the port
							 this->serialPort->BaudRate = 115200;
							 //Open the serial port
							 this->serialPort->Open();
							 this->progressBar1->Value = 100;
						 }
						 else
							 MessageBox::Show("Port couldn't be openned", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error, MessageBoxDefaultButton::Button1);
					 }
					 catch (UnauthorizedAccessException^ ex){
						 MessageBox::Show(ex->Message, "Error occurred", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
					 }
				 }
			}
		 private: System::Void serialPort_DataRecived(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
			 {
				 String^ indata = this->serialPort->ReadLine();
				 SetTextBoxDtype ^pfnDelegate = gcnew SetTextBoxDtype(this, &Main::setText);
				 this->txtRecived->Invoke(pfnDelegate, indata);
			 }
				  void setText(String ^indata){

						  try {

							txtRecived->AppendText(indata);
							txtRecived->AppendText("\n");

							txtRecived->ScrollToCaret();

						  }

						  catch (Win32Exception^ ex)

						  {

							  Console::WriteLine(ex->Message);
						  }

					  
				  }
			 
		private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {

					 this->serialPort->Close();

					 this->progressBar1->Value = 0;

		}
};
}