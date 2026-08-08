#define _USE_MATH_DEFINES
#include<fstream>
#include<iomanip>
#include<iostream>
#include<cmath>
#include<Windows.h>
#include"Robot.h"
#include"MoveCommander.h"
#include"AppMajWindow.h"
#include<vector>
#include<functional>
void printPos(JointPositions* pos) {
	if (pos == nullptr) {
		std::cout << "Position is null." << std::endl;
		return;
	}
	std::cout << "Current Joint Positions: "
			  << "j1: " << pos->j1 << ", "
			  << "j2: " << pos->j2 << ", "
			  << "j3: " << pos->j3 << ", "
			  << "j4: " << pos->j4 << ", "
			  << "j5: " << pos->j5 << ", "
			  << "j6: " << pos->j6 << ", "
			  << "j7: " << pos->j7 << ", "
			  << "j8: " << pos->j8
			  << std::endl;
}

void rotateCur(double deg){
	JointPositions pos;
	controlSystem::GetCurJPos(&pos);
	
	auto pos1 = RinnRobotCommander::MoveCommander::rotateRy(
		Eigen::Vector3d(pos.j4, pos.j5, pos.j6), 
		Eigen::Vector3d(pos.j1, pos.j2, pos.j3), deg/2);
	auto pos2 = RinnRobotCommander::MoveCommander::
		rotateRy(Eigen::Vector3d(pos.j4, pos.j5, pos.j6), 
		Eigen::Vector3d(pos.j1, pos.j2, pos.j3), deg);
	auto pos1_struct = RinnRobotCommander::MoveCommander::newPos(pos1, Eigen::Vector3d(pos.j4, pos.j5 + deg/2, pos.j6));
	auto pos2_struct = RinnRobotCommander::MoveCommander::newPos(pos2, Eigen::Vector3d(pos.j4, pos.j5 + deg, pos.j6));
	controlSystem::MoveArc(&pos1_struct, &pos2_struct);
}
void gethalfdir(double rz_deg, double ry_deg, double &rrz_deg, double &rry_deg)
{
    const double DEG2RAD = M_PI / 180.0;
    double rz = rz_deg * DEG2RAD;
    double ry = ry_deg * DEG2RAD;

    double dx = std::cos(rz) * std::cos(ry);
    double dy = std::sin(rz) * std::cos(ry);
    double dz = std::sin(ry);

    double ix = 1.0, iy = 0.0, iz = 0.0;

    double mx = ix + dx;
    double my = iy + dy;
    double mz = iz + dz;

    double norm = std::sqrt(mx * mx + my * my + mz * mz);

    if (norm < 1e-12) {
        rrz_deg = 0.0; 
        rry_deg = 90.0;
        return;
    }

    double nx = mx / norm;
    double ny = my / norm;
    double nz = mz / norm;

    double ry_new = std::asin((std::max)(-1.0, (std::min)(1.0, nz)));
    double rz_new = std::atan2(ny, nx);
	
	 
    const double RAD2DEG = 180.0 / M_PI;
    rry_deg = ry_new * RAD2DEG;
    rrz_deg = rz_new * RAD2DEG;
}
void rotateCur2(double dry,double drz){
	JointPositions pos;
	controlSystem::GetCurJPos(&pos);
	pos.j1 = 0, pos.j2 = 0, pos.j3 = 0;
	pos.j4 = 0, pos.j5 = 0, pos.j6 = 0;
	std::cout << "Current Joint Positions: "
		<< "j1: " << pos.j1 << ", "
		<< "j2: " << pos.j2 << ", "
		<< "j3: " << pos.j3 << ", "
		<< "j4: " << pos.j4 << ", "
		<< "j5: " << pos.j5 << ", "
		<< "j6: " << pos.j6
		<< std::endl;
	double rry_deg, rrz_deg;
	gethalfdir(drz, dry, rrz_deg, rry_deg);
	auto pos1 = RinnRobotCommander::MoveCommander::
		rotateRyRz(Eigen::Vector3d(pos.j4, pos.j5, 0), 
		Eigen::Vector3d(pos.j1, pos.j2, pos.j3), rry_deg, rrz_deg);
	auto pos2 = RinnRobotCommander::MoveCommander::
		rotateRyRz(Eigen::Vector3d(pos.j4, pos.j5, 0), 
		Eigen::Vector3d(pos.j1, pos.j2, pos.j3), dry, drz);
	std::cout << "pos1: " << rry_deg << ", " << pos1.transpose() << std::endl;
	std::cout << "pos2: " << dry << ", " << drz << ", " << pos2.transpose() << std::endl;
	auto pos1_struct = RinnRobotCommander::MoveCommander::newPos(pos1, Eigen::Vector3d(pos.j4, pos.j5 + rry_deg, pos.j6 + rrz_deg));
	auto pos2_struct = RinnRobotCommander::MoveCommander::newPos(pos2, Eigen::Vector3d(pos.j4, pos.j5 + dry, pos.j6 + drz));
	controlSystem::MoveArc(&pos1_struct, &pos2_struct);
}
bool SavePositionsToTxt(const std::vector<JointPositions>& positions, const std::string& filename, int precision = 6)
{
	if (positions.empty()) {
		return false;
	}

	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		return false;
	}

	outFile << std::fixed << std::setprecision(precision);
	outFile << "start" << "\n";
	outFile << positions.size() << "\n";
	for (const auto& pos : positions) {
		outFile << pos.j1 << " " << pos.j2 << " " << pos.j3 << "\n";
	}

	outFile.close();
	return true;
}
int testmotion(std::function<void()> motionFunc)
{
	int nRtn;
	std::vector<JointPositions> positions;
	JointPositions* pos = new JointPositions();
	JointPositions* mpos = new JointPositions();
	JointPositions* mpos1 = new JointPositions();

	controlSystem::GetCurJPos(pos);
	printPos(pos);
	mpos->j1 = 50, mpos->j2 = 0, mpos->j3 = 0;
	mpos->j4 = 0, mpos->j5 = 0, mpos->j6 = 0;
	//mpos1->j1 = 50, mpos1->j2 = 0, mpos1->j3 = 0;
	//mpos1->j4 = 90, mpos1->j5 = 0, mpos1->j6 = 0;
	std::cout << "start motion test..." << std::endl;
	//motion function

	//controlSystem::SetPtPSpeed(1);
	//controlSystem::MovePTP(mpos);

	controlSystem::SetFeedSpeed(2);

	motionFunc();
	//controlSystem::MoveLine(mpos);
	//rotateCur(20);
	//controlSystem::MoveArc(mpos, mpos1);

	//record positions
	while (true)
	{

		Sleep(10);
		controlSystem::GetCurJPos(pos);
		positions.push_back(*pos);
		int Status = controlSystem::GetMotionStatus();
		if (Status == 1) {
			break;
		}
	}
	std::cout << "end motion test..." << std::endl;
	controlSystem::GetCurJPos(pos);
	printPos(pos);
	SavePositionsToTxt(positions, "C:\\Users\\Administrator\\Desktop\\Robot5\\test\\positions.txt");
	delete mpos1;
	delete mpos;
	delete pos;
	return 0;
}
int main(int argc, char *argv[])
{
	AppMajWindow appWindow;
	appWindow.ShowMajWindow();

	controlSystem::GoHome(1);

	testmotion([](){ rotateCur2(30,30); });

	printEnc();

	return 0;
}