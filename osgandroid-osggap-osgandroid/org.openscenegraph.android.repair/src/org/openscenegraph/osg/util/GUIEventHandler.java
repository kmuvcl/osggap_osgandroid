package org.openscenegraph.osg.util;

import org.openscenegraph.osg.Native;

public class GUIEventHandler implements Native {

	public long _cptr;

	public GUIEventHandler() {
		super();
	}
	public GUIEventHandler(long cptr) {
		super();
		_cptr=cptr;
	}

	public long getNativePtr() {
		return _cptr;
	};

	public void dispose() {
		// TODO Auto-generated method stub
		
	}

}
