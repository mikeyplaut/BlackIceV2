#define Verification

namespace Verification {

	struct AccessLevel {
		int Access;
		bool MenuLocked;
	}Access_t[18];

	typedef enum Access {
		USER,
		VERIFIED,
		VIP,
		ADMIN,
		HOST
	};

	bool hasAccess(int cl, Access Minimum = VERIFIED)
	{
		return Access_t[cl].Access >= Minimum;
	}

	const char* AccessString(Access access) {
		if (access == HOST) return "Host";
		else if (access == ADMIN) return "Admin";
		else if (access == VIP) return "VIP";
		else if (access == VERIFIED) return "Verified";
		else return "USER";
	}

	const char* getAccess(int cl, bool letterOnly)
	{
		if (letterOnly)
		{
			if (Access_t[cl].Access == HOST) return "[^2H^7]";
			else if (Access_t[cl].Access == ADMIN) return "[^1A^7]";
			else if (Access_t[cl].Access == VIP) return "[^4VIP^7]";
			else if (Access_t[cl].Access == VERIFIED) return "[^5V^7]";
			else return "^7[U]";
		}
		else
		{
			if (Access_t[cl].Access == HOST) return "HOST";
			else if (Access_t[cl].Access == ADMIN) return "ADMIN";
			else if (Access_t[cl].Access == VIP) return "VIP";
			else if (Access_t[cl].Access == VERIFIED) return "VERIFIED";
			else return "USER";
		}
	}
	const char* getAccessStr(int cl)
	{
		if (Access_t[cl].Access == HOST) return "^2HOST^7";
			else if (Access_t[cl].Access == ADMIN) return "^1ADMIN^7";
			else if (Access_t[cl].Access == VIP) return "^4VIP^7";
			else if (Access_t[cl].Access == VERIFIED) return "^5VERIFIED^7";
			else return "^7USER";
	}
}