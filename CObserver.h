/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef COBSERVER_H_INCLUDED
#define COBSERVER_H_INCLUDED

#include "Notification.h"

class CObserver
{
public:
	virtual void update(Notification notif) = 0;
};

#endif // COBSERVER_H_INCLUDED