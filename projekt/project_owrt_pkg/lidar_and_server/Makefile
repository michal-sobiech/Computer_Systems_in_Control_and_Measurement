include $(TOPDIR)/rules.mk

PKG_NAME:=lidar_and_server
PKG_VERSION:=1.0
PKG_RELEASE:=1

SOURCE_DIR:=./src
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=lidar_and_server
  CATEGORY:=lidar_and_server
  TITLE:=lidar_and_server
  DEPENDS:=+libstdcpp +libc
endef

define Package/$(PKG_NAME)/description
  Epic lidar with epic server
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)" clean
	$(MAKE) -C "$(PKG_BUILD_DIR)" \
			CXX="$(TARGET_CXX)" \
			CXXFLAGS="$(TARGET_CXXFLAGS)" \
			CC="$(TARGET_CC)" \
			CFLAGS="$(TARGET_CFLAGS)" \
			LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lidar_and_server $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,$(PKG_NAME)))
