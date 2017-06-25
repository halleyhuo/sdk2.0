#include <os_wrapper.h>
#include <log.h>
#include <host_apis.h>
#include <cli/cmds/cli_cmd_wifi.h>
#include <httpserver_raw/httpd.h>
#include <SmartConfig/SmartConfig.h>
#include <net_mgr.h>
#include <lwip/sockets.h>
#include <lwip/netif.h>
#include <lwip/ip_addr.h>
#include "lwip/udp.h"
#include "lwip/igmp.h"
#include "wifi_porting.h"

extern u16 g_SconfigChannelMask;
extern u32 g_sconfig_solution;

struct AP_RECORD *pApJoiningRecord = NULL;

void Switch2STAmode(void)
{
	Sta_setting sta;
	MEMSET(&sta, 0 , sizeof(Sta_setting));
	sta.status = TRUE;
	
	if (netmgr_wifi_control_async(SSV6XXX_HWM_STA, NULL, &sta) == SSV6XXX_FAILED)
	{
		LOG_PRINTF("\nSwtich to STAmode fail\n");
	}
	else
	{
		LOG_PRINTF("\nSwtich to STAmode success\n");
	}
}

int16_t Switch2SCONFIGmode(void)
{
	uint16_t channel = 0x3ffe;
	Sta_setting sta;
	MEMSET(&sta, 0 , sizeof(Sta_setting));
	sta.status = TRUE;
	if(netmgr_wifi_control_async(SSV6XXX_HWM_SCONFIG, NULL, &sta)!= SSV6XXX_SUCCESS)
	{
		LOG_PRINTF("SCONFIG mode fail1\r\n");
		return -1;
	}

	vTaskDelay(2000);  //¹Ø¼üdelay

	g_sconfig_solution=WECHAT_AIRKISS_IN_FW;

	if(netmgr_wifi_sconfig_async(channel)!= SSV6XXX_SUCCESS)
	{
		LOG_PRINTF("SCONFIG mode fail2\r\n");
		return -1;
	}

	return 1;
}

void PrintfScanWifiResult(void)
{
	u32 i=0,AP_cnt;
	s32     pairwise_cipher_index=0,group_cipher_index=0;
	u8      sec_str[][7]= {"OPEN","WEP40","WEP104","TKIP","CCMP"};
	u8  ssid_buf[MAX_SSID_LEN+1]= {0};
	Ap_sta_status connected_info;

	struct ssv6xxx_ieee80211_bss *ap_list = NULL;
	AP_cnt = ssv6xxx_get_aplist_info((void *)&ap_list);


	MEMSET(&connected_info , 0 , sizeof(Ap_sta_status));
	ssv6xxx_wifi_status(&connected_info);

	if((ap_list==NULL) || (AP_cnt==0))
	{
		LOG_PRINTF("AP list empty!\r\n");
		return;
	}
	for (i=0; i<AP_cnt; i++)
	{
	
		if(ap_list[i].channel_id!= 0)
		{
			LOG_PRINTF("BSSID: %02x:%02x:%02x:%02x:%02x:%02x\r\n",
			ap_list[i].bssid.addr[0],  ap_list[i].bssid.addr[1], ap_list[i].bssid.addr[2],  ap_list[i].bssid.addr[3],  ap_list[i].bssid.addr[4],  ap_list[i].bssid.addr[5]);
			MEMSET((void*)ssid_buf,0,sizeof(ssid_buf));
			MEMCPY((void*)ssid_buf,(void*)ap_list[i].ssid.ssid,ap_list[i].ssid.ssid_len);
			LOG_PRINTF("SSID: %s\t", ssid_buf);
			LOG_PRINTF("@Channel Idx: %d\r\n", ap_list[i].channel_id);
			if(ap_list[i].capab_info&BIT(4)) {
				LOG_PRINTF("Secure Type=[%s]\r\n",
							ap_list[i].proto&WPA_PROTO_WPA?"WPA":
							ap_list[i].proto&WPA_PROTO_RSN?"WPA2":"WEP"
							);

				if(ap_list[i].pairwise_cipher[0]) {
					pairwise_cipher_index=0;
					LOG_PRINTF("Pairwise cipher=");
					for(pairwise_cipher_index=0; pairwise_cipher_index<8; pairwise_cipher_index++) {
						if(ap_list[i].pairwise_cipher[0]&BIT(pairwise_cipher_index)) {
							LOG_PRINTF("[%s] ",sec_str[pairwise_cipher_index]);
						}
					}
					LOG_PRINTF("\r\n");
				}
				if(ap_list[i].group_cipher) {
					group_cipher_index=0;
					LOG_PRINTF("Group cipher=");
					for(group_cipher_index=0; group_cipher_index<8; group_cipher_index++) {
						if(ap_list[i].group_cipher&BIT(group_cipher_index)) {
							LOG_PRINTF("[%s] ",sec_str[group_cipher_index]);
						}
					}
					LOG_PRINTF("\r\n");
				}
			} else {
				LOG_PRINTF("Secure Type=[NONE]\r\n");
			}
	
			if(!memcmp((void *)ap_list[i].bssid.addr,(void *)connected_info.u.station.apinfo.Mac,ETHER_ADDR_LEN)) {
				LOG_PRINTF("RSSI=-%d (dBm)\r\n",ssv6xxx_get_rssi_by_mac((u8 *)ap_list[i].bssid.addr));
			}
			else {
				LOG_PRINTF("RSSI=-%d (dBm)\r\n",ap_list[i].rxphypad.rpci);
			}
			LOG_PRINTF("\r\n");
		}
	
	}
	FREE((void *)ap_list);
}

void ScanWifi(void)
{
	netmgr_wifi_scan_async(0xffff, NULL, 0);
}

void LeaveWifi(void)
{
	int ret = -1;
	ret = netmgr_wifi_leave_async();
	if (ret != 0)
	{
		LOG_PRINTF("netmgr_wifi_leave failed !!\r\n");
	}
}

void JoinWifi(const uint8_t *ssidName, const uint8_t *ssidPassword)
{
	int ret = -1;
	wifi_sta_join_cfg *join_cfg = NULL;
	
	join_cfg = (wifi_sta_join_cfg *)MALLOC(sizeof(wifi_sta_join_cfg));
	
	memset(join_cfg,0,sizeof(wifi_sta_join_cfg));
	
	memcpy(join_cfg->ssid.ssid, ssidName, strlen(ssidName));
	join_cfg->ssid.ssid_len = strlen(ssidName);
	memcpy(join_cfg->password, ssidPassword, strlen(ssidPassword));

	ret = netmgr_wifi_join_async(join_cfg);
	if (ret != 0)
	{
		LOG_PRINTF("netmgr_wifi_join_async failed !!\r\n");
	}

	FREE(join_cfg);
}

int16_t GetNetifStatus(void)
{
	struct netif *netif;

	netif = netif_find(WLAN_IFNAME);
	if (netif)
	{
		return netif_is_up(netif);
	}
	return 0;
}

/**
* @brief
* 	 Get IP address
*
* @param
*
* @return
* 	 Ip address
*/
uint32_t GetIpAdress(void)
{
	ipinfo info;
	
	netmgr_ipinfo_get(WLAN_IFNAME, &info);
	return info.ipv4;
}

uint8_t FindApInWifiList(uint8_t n, uint32_t ap_count, struct ssv6xxx_ieee80211_bss *ap_list)
{
	u32 i=0;
	uint8_t ret=0;
	
	if((ap_list==NULL) || (ap_count==0))
	{
		LOG_PRINTF("AP list empty!\r\n");
		return 0;
	}
	for (i=0; i<ap_count; i++)
	{
		if(ap_list[i].channel_id!= 0)
		{
			if(pApJoiningRecord->ssid_pwd[n].ssid_len == ap_list[i].ssid.ssid_len)
			{
				if(memcmp((void *)&pApJoiningRecord->ssid_pwd[n].ssid[0], (void*)ap_list[i].ssid.ssid, pApJoiningRecord->ssid_pwd[n].ssid_len) == 0)
				{
					ret = 1;
					break;
				}
			}
		}
	}
	return ret;
}


void SconfigScanDone (void *data)
{
	struct resp_evt_result *sconfig_done = (struct resp_evt_result *)data;
	if(sconfig_done->u.sconfig_done.result_code==0) {
		if(pApJoiningRecord->total_items == 0) {
			pApJoiningRecord->current_item = 0;
		}
		else {
			pApJoiningRecord->current_item  += 1;
			pApJoiningRecord->current_item %= TOTAL_WIFI;
		}
	
		if(pApJoiningRecord->total_items < TOTAL_WIFI)
		{
			pApJoiningRecord->total_items++;
		}
		memset(pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].ssid,0,SSID_LEN);
		memcpy((void*)pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].ssid, (void*)sconfig_done->u.sconfig_done.ssid, sconfig_done->u.sconfig_done.ssid_len);
		pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].ssid_len = sconfig_done->u.sconfig_done.ssid_len;
		memset(pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].password,0,PASSWORD_LEN);
		sprintf(pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].password,"%s",sconfig_done->u.sconfig_done.pwd);
		pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].password_len =strlen(pApJoiningRecord->ssid_pwd[pApJoiningRecord->current_item].password);
		set_sconfig_flag(1);
	}
	return;
}

#if 0
void _host_event_handler(u32 evt_id, void *data, s32 len)
{
	switch (evt_id) {
	case SOC_EVT_LOG:
		//LOG_PRINTF("SOC_EVT_LOG\n");
		//_soc_evt_handler_ssv6xxx_log(evt_id, data, len);
		break;
	case SOC_EVT_SCAN_RESULT:
		_scan_result_handler(data);
		break;
	case SOC_EVT_SCAN_DONE:
		_scan_down_handler(data);
		break;
	case SOC_EVT_SCONFIG_SCAN_DONE:
		_sconfig_scan_done(data);
		break;
	case SOC_EVT_GET_SOC_STATUS:
		_soc_evt_get_soc_status(data);
		break;
#if (CONFIG_BUS_LOOPBACK_TEST)
	case SOC_EVT_BUS_LOOPBACK:
		_bus_loopback_handler(data);
		break;
#endif
#ifdef USE_CMD_RESP
	case SOC_EVT_CMD_RESP:
		_handle_cmd_resp(evt_id, data, len);
		break;
	case SOC_EVT_DEAUTH:
		if(g_cli_ps_lp)
		{
			os_cancel_timer(cli_ps_t_handler,(void*)1,NULL);
			os_cancel_timer(cli_ps_t_handler,(void*)2,NULL);
		}
		_deauth_handler(data);
		break;
#else // USE_CMD_RESP
	case SOC_EVT_JOIN_RESULT:
		_join_result_handler(data);
		break;
	case SOC_EVT_LEAVE_RESULT:
		g_cli_joining=false;
		if(g_cli_ps_lp)
		{
			os_cancel_timer(cli_ps_t_handler,(void*)1,NULL);
			os_cancel_timer(cli_ps_t_handler,(void*)2,NULL);
		}
		_leave_result_handler(data);
		break;
	case SOC_EVT_GET_REG_RESP:
		_get_soc_reg_response(evt_id, data, len);
		break;
	
	/*=================================================*/
#endif // USE_CMD_RESP

	case SOC_EVT_POLL_STATION://sending arp request event
	case SOC_EVT_STA_STATUS://sending station add/remove event
	
		break;
	case SOC_EVT_PS_WAKENED:
		printf("&&&&&& _host_event_handler: SOC_EVT_PS_WAKENED.\n");
		_set_wifi_state(0);
		if(g_cli_ps_lp)
		{
			MsgEvent *msg_evt = NULL;
			msg_evt = msg_evt_alloc();
			if(NULL!=msg_evt)
			{
				msg_evt->MsgType = MEVT_HOST_CMD;
				msg_evt->MsgData = SOC_EVT_PS_WAKENED;
				msg_evt_post(CLI_MBX, msg_evt);
			}
			else
			{
				LOG_PRINTF("%s:msg alloc fail for SOC_EVT_PS_WAKENED\r\n",__FUNCTION__);
			}
		}
		break;
	case SOC_EVT_PS_SETUP_OK:
		break;
	default:
		LOG_PRINTF("Unknown host event received. %d\r\n", evt_id);
		break;
	}
} // end of - host_event_handler -
#endif


