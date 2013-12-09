package org.openscenegraph.osg.util;

import org.openscenegraph.osg.Library;
import org.openscenegraph.osg.Native;
import org.openscenegraph.osg.core.Node;

import android.util.Log;

public class PickHandler extends GUIEventHandler {
	static {
		Library.initLibrary();
	}
	private static String TAG = "org.openscenegraph.osg.util.PickHandler";
	private static final boolean DEBUG = false;

	/**
	 * @return native pointer to the viewer
	 */
	private static native long nativeCreatePickHandler();

	private static native void nativeDisposePickHandler(long cptr);
	
	private native long nativeGetOrCreateSelectionBox(long cptr);
	
	public PickHandler() {
		super();
		_cptr = nativeCreatePickHandler();
	}

	public void dispose() {
		Log.i(TAG, "Disposing PickHandler");
		if (_cptr != 0)
			nativeDisposePickHandler(_cptr);
		_cptr = 0;
	}
	
	public Node getOrCreateSelectionBox() {
		long cptr = nativeGetOrCreateSelectionBox(_cptr);
		if(cptr == 0)
			return null;
		return new Node(cptr);
	}

}
