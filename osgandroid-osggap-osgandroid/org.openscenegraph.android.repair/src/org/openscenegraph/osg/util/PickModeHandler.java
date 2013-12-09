package org.openscenegraph.osg.util;

import org.openscenegraph.osg.Library;
import org.openscenegraph.osg.core.MatrixTransform;
import org.openscenegraph.osg.core.Node;

import android.util.Log;

public class PickModeHandler extends GUIEventHandler {
	static {
		Library.initLibrary();
	}
	private static String TAG = "org.openscenegraph.osg.util.PickModeHandler";
	private static final boolean DEBUG = false;

	/**
	 * @return native pointer to the viewer
	 */
	private static native long nativeCreatePickModeHandler();

	private static native void nativeDisposePickModeHandler(long cptr);

	private static native long nativeAddDraggerToScene(long cptr, long n_cptr, String str);

	private static native long nativeGetSelectedNode(long cptr);
	
	private static native void nativeChangeScaleAndRotateSelectedNode(long cptr, float scale, float degree, int x, int y);
	
	private static native int nativeIsSelect(long cptr);
	
	public PickModeHandler() {
		super();
		_cptr = nativeCreatePickModeHandler();
	}

	public void dispose() {
		Log.i(TAG, "Disposing PickHandler");
		if (_cptr != 0)
			nativeDisposePickModeHandler(_cptr);
		_cptr = 0;
	}
	
	//return node must be child of MatrixTransform if you used changeScaleAndRotateSelectedNode function
	public Node addDraggerToScene(Node node, String str) {
		long cptr = nativeAddDraggerToScene(_cptr, node.getNativePtr(), str);
		if(cptr == 0)
			return null;
		return new Node(cptr);
	}

	//TabBoxDragger only
	public synchronized long getSelectedNode() {
		long cptr = nativeGetSelectedNode(_cptr);
		if(cptr == 0)
			return 0;
		Log.d("onTouch", "now cptr: "+cptr);
		return cptr;
	}
	
	//TabBoxDragger only
	public synchronized void changeScaleAndRotateSelectedNode(float scale, float degree, int x, int y) {
		nativeChangeScaleAndRotateSelectedNode(_cptr, scale, degree, x, y);
	}
	
	public synchronized int isSelect() {
		return nativeIsSelect(_cptr);
	}
	

}
