#include "AppWindow.h"

int main() {
	AppWindow app;
	if (app.init()) {
		app.initialize();
		while (app.isRun()) {
			app.broadcast();
		}
	}
	return 0;
}