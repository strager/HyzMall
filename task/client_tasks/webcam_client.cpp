#include "webcam_client.h"


webcam_client::webcam_client()
{
	path = "user/results_webcam";
}


webcam_client::~webcam_client()
{
}

void webcam_client::execute()
{
	
	auto funct = fetch_function(results["method"]);
	funct();
}

void webcam_client::on_execute()
{
	send_results(file_name, true);
	results["completed"] = true;
}


bool webcam_client::one_capture()
{
	cv::VideoCapture _cap;
	srand(time(NULL));
	// TODO - rafael - change real path
	file_name = "c://" + std::to_string(rand() % 100000) + ".jpg";

	if (!_cap.open(0))
		return false;

	cv::Mat frame;
	_cap >> frame;

	if (frame.empty())
		return false;


	cv::imwrite(file_name, frame);
	results["image_name"] = file_name;
	return true;
}

bool webcam_client::video_capture()
{
	// TODO - rafael - create function to capture video
	return true;
}

void webcam_client::run(
	std::string id,
	bool response,
	std::string method,
	std::vector<std::string> args
) {
	base_task::run(id, response, method, args);
}

bool webcam_client::check_webcam()
{
	return true;
}

_function webcam_client::fetch_function(std::string _function_name)
{
	if (_function_name == "one_capture")
		return std::bind(&webcam_client::one_capture, this);

	return std::bind(&webcam_client::one_capture, this);
}