/*
* This source file is part of Linear-oscillator_QThread.
*
* Copyright (c) 2013 Linear-oscillator_QThread <https://github.com/IL90/Linear-oscillator_QThread>
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow wgt;
	wgt.show();
	return app.exec();
}
