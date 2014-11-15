/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include "DemoScene.h"
#include <iostream>
#include <exception>
#include "DemoInterface.h"
#include "CGFapplication.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new DemoScene());
		app.setInterface(new DemoInterface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}