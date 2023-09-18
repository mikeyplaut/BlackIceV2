#define Aimbot

namespace Aimbot{
	float Vec3DistanceSq(float* veca, float* vecb) {
		float x = (vecb[0] - veca[0]);
		float y = (vecb[1] - veca[1]);
		float z = (vecb[2] - veca[2]);
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	bool Scr_Closer(float* startingPoint, float* trueIfCloser, float* falseIfCloser) {
		float firstDistance = Vec3DistanceSq(startingPoint, trueIfCloser);
		float secondDistance = Vec3DistanceSq(startingPoint, falseIfCloser);
		return (firstDistance < secondDistance);
	}

	opd_s G_irand_t = { 1819488, TOC };
	int(*G_irand)(int min, int max) = (int(*)(int, int))&G_irand_t;

	//0x00052738   given:1823640
	opd_s G_DObjGetWorldTagPos_t = {1823640, TOC };
	int(*G_DObjGetWorldTagPos)(gentity_s* ent, int tagName, float* out) = (int(*)(gentity_s*, int, float*))&G_DObjGetWorldTagPos_t;

	opd_s SL_GetString_t = { 0x2013A8, TOC };
	int SL_GetString(const char* string) {
		int(*SL_GetString)(const char* string, int user) = (int(*)(const char*, int))&SL_GetString_t;
		return SL_GetString(string, 0);
	}

	//0x001AE8F8   given:0x1AEB90
	opd_s Scr_PlayerDamage_t = { 0x1AEB90, TOC };
	void(*Scr_PlayerDamage)(gentity_s * self, gentity_s *inflictor, gentity_s *attacker, int damage, int dflags, int meansOfDeath, int iweapon, const float *vPoint, const float *vDir, int hitLoc, int timeOffset) = (void(*)(gentity_s *, gentity_s*, gentity_s*, int, int, int, int, const float*, const float*, int, int))&Scr_PlayerDamage_t;

	char* randHitLoc()
	{
	int rand = G_irand(0, 11);
	switch (rand)
	{
		case 0: return "j_neck";
		case 1: return "j_hip_le";
		case 2: return "j_wrist_le";
		case 3: return "j_shoulder_le";
		case 4: return "j_elbow_le";
		case 5: return "j_spinelower";
		case 6: return "j_shoulder_ri";
		case 7: return "j_spineupper";
		case 8: return "j_spine4";
		case 9: return "j_knee_le";
		case 10: return "j_ankle_ri";
	}
	}
	
	gentity_s* g_entities = (gentity_s*)20027392;
	dvar_s* ui_gametype = (dvar_s*)0x1D10028;

	bool killcamTimer[18];
	bool UnfairAim[18];
	void SilentAimbotNoHead1(int clientNum)
	{
		gentity_s* self = &g_entities[clientNum];
		gclient_s* client = self->client;
		gentity_s* target = 0, *possibleTarget = 0;
		gclient_s* possibleClientTarget = 0;
		for (int i = 0; i < 12; i++) 
		{
			possibleTarget = &g_entities[i];
			possibleClientTarget = possibleTarget->client;
			if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
				continue;
		
			if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
				target = possibleTarget;
		}
		if (target){
			int rand = G_irand(0, 10);
			int timeOffset = killcamTimer[clientNum];
			if (timeOffset == 1337) { //Random timers
				int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
			if (rand == 9)
				timeOffset = 43;
			}
			else
				timeOffset = 200;
			}
			vec3_1 bulletDestination;
			char* hitLoc = randHitLoc();
			if (rand >= 4)
				G_DObjGetWorldTagPos(target, SL_GetString("j_head"), bulletDestination);
			else
				G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);

			Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 4 ? 0x9 : 0x2), self->client->ps.weapon.data, bulletDestination, bulletDestination, 0x4, timeOffset);
		}
	}
}