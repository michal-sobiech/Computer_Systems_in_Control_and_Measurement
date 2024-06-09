include $(TOPDIR)/rules.mk

PKG_NAME:=pdlidar
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=lidarpd
  CATEGORY:=lidarpd
  TITLE:=lidarpd
  DEPENDS:=+libstdcpp +libc
endef

define Package/$(PKG_NAME)/description
  Epic homework with radar visualisation
endef

define Build/Compile
	$(info AAAAAAAAAAAAAAAAAAAAAAAAAA: $(PKG_BUILD_DIR))
	$(MAKE) -C "$(PKG_BUILD_DIR)" clean
	$(MAKE) -C $(PKG_BUILD_DIR) \
			CXX="$(TARGET_CXX)" \
			CXXFLAGS="$(TARGET_CXXFLAGS)"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fake_lidar $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,$(PKG_NAME)))
