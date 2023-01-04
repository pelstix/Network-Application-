/*
 * Created on Tue Apr 07 2021
 *
 * Copyright (c) 2021 - Mathéo G & Sahel H - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Cpp-Network-App
 */

#pragma once

#ifndef COBSERVABLE_H_INCLUDED
#define COBSERVABLE_H_INCLUDED

#include "CObserver.h"
#include "Notification.h"
#include <wx/wx.h>

class CObservable
{
private:
	CObserver* m_observer;

public:
	void atach(CObserver* observer);
	void detach();

	virtual void notify(Notification);
};

#endif // COBSERVABLE_H_INCLUDED