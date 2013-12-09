package org.openscenegraph.osg.util;

import org.openscenegraph.osg.Library;
import org.openscenegraph.osg.Native;
import org.openscenegraph.osg.core.Matrix;

import android.util.Log;

public class TrackballManipulator extends GUIEventHandler {
	static {
		Library.initLibrary();
	}
	
	private static String TAG = "org.openscenegraph.osg.util.TrackballManipulator";
	private static final boolean DEBUG = false;
	
	/**
	 * @return native pointer to the viewer
	 */
	private static native long nativeCreateTrackballManipulator();
	private static native void nativeDispose(long cptr);
	private native long nativeGetMatrix(long cptr);

	public TrackballManipulator() {
		super();
		_cptr = nativeCreateTrackballManipulator();		
	}
	
	public Matrix getMatrix() {
		long cptr = nativeGetMatrix(_cptr);
		if(cptr == 0)
			return null;
		return new Matrix(cptr);
	}
	
	public void dispose() {
		Log.i(TAG, "Disposing TrackballManipulator");
		if (_cptr != 0)
			nativeDispose(_cptr);
		_cptr = 0;
	}

}
