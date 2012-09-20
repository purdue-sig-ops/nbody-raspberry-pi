/*
 * The ClientInfo struct is used to send the server
 * relevant info such as benchmarks on the client system,
 * available memory, preferred work unit size, etc so the
 * server can assign appropriate work units
 *
 * For the initial versions of this, this will not really
 * be used, but is instead included to allow for later
 * extensions
 */
typedef struct {
	int id;
	int ip;
	int frame;
} ClientInfo;
