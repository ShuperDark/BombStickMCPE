#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <string>
#include <Substrate.h>

#include "com/mojang/minecraftpe/world/entity/player/Player.h"
#include "com/mojang/minecraftpe/world/item/ItemInstance.h"
#include "com/mojang/minecraftpe/world/item/Item.h"
#include "com/mojang/minecraftpe/world/level/BlockSource.h"
#include "com/mojang/minecraftpe/world/level/Level.h"
#include "com/mojang/minecraftpe/world/phys/Vec3.h"

bool (*_Item_useOn)(Item*, ItemInstance*, Player*, int, int, int, signed char, float, float, float);
bool Item_useOn(Item* self, ItemInstance* itemstack, Player* player, int x, int y, int z, signed char side, float xx, float yy, float zz) {
if(self == Item::mStick) {
player->getLevel().explode(player->getRegion(), 0, Vec3(x, y, z), 10, false);
player->getLevel().playSound(Vec3(x, y, z), "note.harp", 20, 2);
}

return _Item_useOn(self, itemstack, player, x, y, z, side, xx, yy, zz);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*)&Item::useOn,(void*)&Item_useOn,(void**)&_Item_useOn);
	return JNI_VERSION_1_2;
}
