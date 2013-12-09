package org.openscenegraph.osg.core;

import org.openscenegraph.osg.Native;

public class BoundingSphere implements Native {

	private static native long nativeCreateBoundingSphere();
	private static native boolean nativeIntersects(long _cptr, long cptr);
	private static native boolean nativeIsIntersects(long _cptr, long cptr);
	private static native float nativeGetDistanceBetweenTwoNode(long _cptr, long cptr);
	
	protected long _cptr;
	
	public BoundingSphere(long cptr) {
		_cptr=cptr;
	}
	
	public BoundingSphere() {
		_cptr = nativeCreateBoundingSphere();
	}

	public boolean intersects(BoundingSphere bs) {
		return nativeIntersects(_cptr, bs.getNativePtr());
	}

	//temp
	public boolean isIntersects(MatrixTransform mt1, MatrixTransform mt2) {
		return nativeIsIntersects(mt1.getNativePtr(), mt2.getNativePtr());
	}
	//temp
	public float getDistanceBetweenTwoNode(MatrixTransform n1, MatrixTransform n2) {
		return nativeGetDistanceBetweenTwoNode(n1.getNativePtr(), n2.getNativePtr());
	}

	public long getNativePtr() {
		return _cptr;
	}

	public void dispose() {
		// TODO Auto-generated method stub

	}

}
