package org.openscenegraph.osg.core;

import org.openscenegraph.osg.Library;

import android.util.Log;

public class Texture2D extends Texture {
	static {
		Library.initLibrary();
	}
	private static String TAG = "org.openscenegraph.osg.core.Texture2D";
	private static final boolean DEBUG = false;

	/**
	 * @return native pointer to the viewer
	 */
	private static native long nativeCreateTexture2D();
	private static native void nativeDisposeTexture2D(long cptr);
	private static native void nativeSetDataVariance(String s);
	private static native void nativeSetImage(long cptr);
	
	public Texture2D() {
		super();
		_cptr = nativeCreateTexture2D();
	}

	public void dispose() {
		Log.i(TAG, "Disposing PickHandler");
		if (_cptr != 0)
			nativeDisposeTexture2D(_cptr);
		_cptr = 0;
	}

}
