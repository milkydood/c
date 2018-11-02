// just to bodge host id for new support (slimey lost the src to his keygen).
// build with gcc -shared -ldl -fPIC -o a.so <this file>
// LD_PRELOAD/PRELOAD_64=a.so. Remember to include the path in LD_LIBRARY_PATH
long gethostid (void) {
		return 0x80c2c5b6;
}
