#include <windows.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>

void CallBackFunc(int event, int x, int y, int flags, void* userdata);

bool clickValue = false;

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	LPTSTR WINAPI GetCommandLine(void);
	//MessageBox(NULL, lpCmdLine, "Command Line", MB_OK);
	char key;
	
	std::string num = lpCmdLine;
	std::string filePath = "C:\\accesscam\\testing";
	std::string jpg = ".jpg";
	std::string combined = filePath += num += jpg;

	const char * saveName = combined.c_str();
	
	cvNamedWindow("Camera", 1); //Create window
	cvResizeWindow("Camera", 650, 521);
	cvSetMouseCallback("Camera", CallBackFunc, NULL);
	CvCapture* capture = cvCaptureFromCAM(1); //Capture using any camera connected to your system
	while (1){ //Create infinte loop for live streaming
		IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
		cvShowImage("Camera", frame); //Show image frames on created window
		key = cvWaitKey(10); //Capture Keyboard stroke
		if (char(key) == 13 || clickValue == true){ //13 == ASCII for 'Enter'
			cvSaveImage(saveName, frame);
			break; //If you hit Enter key loop will break.
		}
		else if (char(key) == 27){
			break;
		}
	}
	cvReleaseCapture(&capture); //Release capture.
	cvDestroyWindow("Camera"); //Destroy Window
	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		clickValue = true;
	}
}
