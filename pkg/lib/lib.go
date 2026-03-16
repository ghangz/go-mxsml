// "Copyright (c) 2026 MetaX Integrated Circuits (Shanghai) Co., Ltd. All rights reserved."
package lib

import (
	"errors"
	"fmt"
	"os"
	"runtime"
	"sync/atomic"
	"unsafe"
)

// #cgo LDFLAGS: -ldl
// #include <dlfcn.h>
// #include <stdlib.h>
import "C"

var g_mxsmlLib = newMxsmlLib()

type library struct {
	handle   unsafe.Pointer
	loaded   atomic.Bool
	path     string
	flag     int
}

func newMxsmlLib() *library {
	mxsmlLib := &library{
		flag: C.RTLD_LAZY | C.RTLD_GLOBAL,
	}

	mxsmlLib.loaded.Store(false)

	return mxsmlLib
}

func Load() error {
	if g_mxsmlLib.loaded.Load() {
		return nil
	}

	// check lib path
	libPathList := []string{"/opt/mxdriver/lib/libmxsml.so", "/opt/maca/lib/libmxsml.so", "/opt/mxn100/lib/libmxsml.so"}
	for _, path := range libPathList {
		if _, err := os.Stat(path); err == nil {
			g_mxsmlLib.path = path
			break
		}
	}

	if len(g_mxsmlLib.path) == 0 {
		return fmt.Errorf("invalid mxsml lib path")
	}

	libPath := C.CString(g_mxsmlLib.path)
	defer C.free(unsafe.Pointer(libPath))

	runtime.LockOSThread()
	defer runtime.UnlockOSThread()

	handle := C.dlopen(libPath, C.int(g_mxsmlLib.flag))
	if handle == nil {
		return getDlError()
	}

	g_mxsmlLib.handle = handle
	g_mxsmlLib.loaded.Store(true)
	return nil
}

func Unload() error {
	if g_mxsmlLib.handle == nil {
		return nil
	}

	runtime.LockOSThread()
	defer runtime.UnlockOSThread()

	if C.dlclose(g_mxsmlLib.handle) != 0 {
		return getDlError()
	}

	g_mxsmlLib.handle = nil
	g_mxsmlLib.loaded.Store(false)
	return nil
}

func getDlError() error {
	lastErr := C.dlerror()
	if lastErr != nil {
		return errors.New(C.GoString(lastErr))
	}

	return nil
}
