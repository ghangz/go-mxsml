// "Copyright (c) 2026 MetaX Integrated Circuits (Shanghai) Co., Ltd. All rights reserved."
package utils

import (
	"unsafe"
)

func BytePtrToStr(ptr *byte) string {
	if ptr == nil {
		return ""
	}

	len := 0
	p := ptr
	for *p != 0 {
		len++
		p = (*byte)(unsafe.Pointer(uintptr(unsafe.Pointer(p)) + 1))
	}

	return string(unsafe.Slice(ptr, len))
}

func ExtractValidString(arr []byte) string {
	arrLen := len(arr)
	var i int
	for ; i < arrLen; i++ {
		if arr[i] == 0 {
			break
		}
	}

	return string(arr[:i])
}
