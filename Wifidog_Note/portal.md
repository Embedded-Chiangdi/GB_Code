## Captive Portal
A comprehensive guide of Captive Portal.
### What is Captive Portal
A captive portal, used to present a landing or log-in page which require authentication, is a web page that when device newly connected to a public WIFI before network's access is granted. Often portals automatically opens in a web browser or when the user opens a web browser.
### Implementation of Captive Portal
* HTTP Redirect
* DNS Redirect
#### DNS Redirect
DNS redirection works as the simple DNS hijacking where all the user DNS requests are hijacked and resolved to the captive portal login page.
#### HTTP Redirect
when a client newly connect to a WIFI, it sends a http requests to detect captive portal. if device receive a HTTP message which is HTTP 204 status code, it assumes it can access internet. Otherwise, this client will received a HTTP message, which is HTTP status code of 302 or 307(redirect) , to the captive portal. We will explain much more details about this way as follow.
##### Captive Portal Detection method by various Operating Systems Platform
###### Android 4 – 9
Android devices look for an HTTP 204 response for a file named generate_204 from the following domain.
```
#Base on Samsung S8
connectivity.samsung.com.cn
mtalk.google.com
play.googleapis.com
#A much more common website of Android
clients3.google.com
connectivitycheck.android.com
connectivitycheck.gstatic.com
```
HTTP Status 204 means the file exists but, is empty. This lets Android know that the Internet is accessible. If the request receives HTTP Status 302 (temporary redirect) instead of HTTP 204, Android will follow the redirection URL to display the Captive Portal to the user.
###### Windows
```
www.msftconnecttest.com
www.msftncsi.com
```
Windows uses hardcoded IPv4 and ipv6 addresses to match the request response to verify the Internet connection. Though it can be spoofed for availability pretty easily.
###### Apple IOS 7+ and recent versions of MACos(10.10+)
```
captive.apple.com/hotspot-detect.html
www.apple.com/library/test/success.html
```
Apple's device is quiet different from others because of `WISPr`.
> WISPr (pronounced “whisper”) or Wireless Internet Service Provider roaming used by every Apple device for captive portal detection. This technology allows users to roam between wireless internet service providers in a fashion similar to that which allows cell phone users to roam between carriers.

When an iDevice connects to a Wi-Fi network, the first thing it does is make a request to the URL captive.apple.com or apple.com/test/success.html.With iOS 7 onwards, Apple began to use the User Agent “CaptiveNetworkSupport“, though it’s not as common as the URL method that Android and Windows uses. It sends out a request to the above URL. If the request gets redirected, then Apple knows there is a portal. It then launches a dialog box, containing Safari, to give you a chance to log in.

The reason Apple does this is because you may be using an app other than the web browser. For example, the only thing you might be doing is syncing your e-mail. In such situations, you would never see the portal page, and your app will mysteriously fail to connect to the Internet.

Therefore, before your app has a chance to access the network, Apple does this for you. It sends out a request to the above URL. If the request gets redirected, then Apple knows there is a portal. It then launches a dialog box, containing Safari, to give you a chance to login.

The following is the sniffed version of the HTTP request:
```
GET /hotspot-detect.html HTTP/1.0\r\n
Request URI: /hotspot-detect.html
Host: captive.apple.com\r\n
User-Agent: CaptiveNetworkSupport-355.270.2 wispr\r\n
```
### Reference Reading
* [Captive portal-Wikepedia](https://en.wikipedia.org/wiki/Captive_portal)
* [CAPTIVE PORTAL The Definitive Guide](https://rootsh3ll.com/captive-portal-guide/)
* [captive portal](https://searchmobilecomputing.techtarget.com/definition/captive-portal)
* [Why apple's device Captive page very slow](https://forums.developer.apple.com/thread/113712)
* [Solving the Captive Portal Problem on iOS](https://medium.com/@rwbutler/solving-the-captive-portal-problem-on-ios-9a53ba2b381e)
* [Apple's secret "wispr" request](https://blog.erratasec.com/2010/09/apples-secret-wispr-request.html#.Xed3N-gzaHs)
* [portal认证的几种实现方式](http://cxd2014.github.io/2017/05/21/portal-auth/)