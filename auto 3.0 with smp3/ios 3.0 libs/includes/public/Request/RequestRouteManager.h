//
//  RouteManager.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Request.h"

@interface RequestCookieJar : NSObject

-(void)setCookie:(Request*) request;
-(void)storeCookie:(Request*)response;
-(void)resetCookie;

@end

@interface RequestRoute : NSObject {
    
    NSString *m_domain;
    NSString *m_securityConfig;
    NSString *m_appConnectionId;
    NSString *m_supHostPort;
    NSString *m_realm;
    NSString *m_authSchema;
    
    SecIdentityRef m_secRefID;
    
    NSDictionary *m_authHeaderNwEdge;
    RequestCookieJar *m_cookieJar;
}

@property(nonatomic,retain) NSString *m_domain;
@property(nonatomic,retain) NSString *m_securityConfig;
@property(nonatomic,retain) NSString *m_appConnectionId;
@property(nonatomic,retain) NSString *m_supHostPort;
@property(nonatomic,retain) NSString *m_realm;
@property(nonatomic,retain) NSString *m_authSchema;
@property(nonatomic,retain) RequestCookieJar *m_cookieJar;

@property(nonatomic,retain)  NSDictionary *m_authHeaderNwEdge;

-(void)addHeaders:(Request*)request;


////For mutual SSL
-(void)setClientCertificateFromRoute:(Request*)request;
-(void)setSecurityIdenRef:(SecIdentityRef)p_securityIdenRef;


@end

@interface RequestRouteManager : NSObject

+(RequestRoute*)getRoute:(NSString*)url;


@end

