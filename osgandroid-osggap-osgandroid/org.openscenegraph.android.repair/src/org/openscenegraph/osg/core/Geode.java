package org.openscenegraph.osg.core;

import org.openscenegraph.osg.Library;

public class Geode extends Node {
	static {
		Library.initLibrary();
	}
	private static native long nativeCreateGeode();
	private static native void nativeDispose(long cptr);
	private static native void nativeGetSphere(long cptr, float x, float y, float z, float radius);
	private static native void nativeGetCube(long cptr, float x1, float y1, float z1, float x2, float y2, float z2 );
	private static native void nativeGetTextureRectangle(long cptr, float width, float height, String fileName );
	private static native void nativeGetTextureRectangle2(long cptr, long imagecptr, float width, float height );
	
	public Geode(long cptr) {
		super(cptr);	
	}
	
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
	public Geode() {
		_cptr = nativeCreateGeode();
	}
	
	public void getSphere(Vec3 center, float radius) {
		nativeGetSphere(_cptr,center.x(),center.y(),center.z(),radius);
	}
	
	public void getCube(Vec3 center, float lx, float ly, float lz) {
		nativeGetCube(_cptr,center.x(),center.y(),center.z(),lx,ly,lz);
	}

	public void getTextureRectangle(float width, float height, String fileName) {
		nativeGetTextureRectangle(_cptr, width, height, fileName);
	}
	public void getTextureRectangle(float width, float height, Image image) {
		nativeGetTextureRectangle2(_cptr, image.getNativePtr(), width, height);
	}


}
