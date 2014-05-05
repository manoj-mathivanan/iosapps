//
//  ODataEntryXMLBuilder.h
//  Parser
//
//  Created by Farkas, Zoltan on 04/29/11.
//  Copyright 2011 SAP AG. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Contains the XML representation of an entry
 * and the HTTP method that must be used when 
 * issuing a request with the above mentioned XML against the backend.
 */

@interface ODataEntryBody : NSObject {
	NSString*	body;
	NSString*	m_Method;
}

@property (nonatomic, retain) NSString* body;
@property (nonatomic, retain) NSString* method;

-(id)init;
@end


/**
 * Builder class that creates an XML representation of an entry
 * The builder considers if the entry is used for updating or creating data
 * in the backend.
 */
enum TEN_ENTRY_OPERATIONS {
	ENTRY_OPERATION_CREATE				= 0, ///< From OData4SAP v1.03: "As new entities are created using the POST method, and this method is not idempotent: entity types SHOULD have a key whose values are provided by the client."
	ENTRY_OPERATION_UPDATE_FULL			= 1,
	ENTRY_OPERATION_UPDATE_INCREMENTAL	= 2,
	ENTRY_OPERATION_ARCHIVE				= 3,  ///< Used when an entry should be saved as an xml file and is not sent to the server. This causes the builder to add the links and icon url (if present) too to the xml.
    ENTRY_OPERATION_CREATE_MINIMAL      = 4,
    ENTRY_OPERATION_UPDATE_FULL_MINIMAL = 5,
    ENTRY_OPERATION_UPDATE_INCREMENTAL_MINIMAL  = 6
    
    
};

/**
 Enum for buld styles of JSON and ATOM 
 */
enum BUILD_STYLE
{
    BUILD_STYLE_ATOM_XML  = 0, //Use this when you want to build an atom xml body
    BUILD_STYLE_ATOM_FEED = 1, //DO_NOT_USE!
    BUILD_STYLE_JSON      = 2  //Use this when you want to build a json body
};


@class ODataServiceDocument;
@class ODataEntry;

/**
 * Returns the atom/json representation of an entry or feed depending on the operation and the HTTP method that must be used when the atom/json is sent to the server
 * in an HTTP request.
 * @param payload The payload from which the function creates its representation.This could be either an ODataEntry (@see ODataEntry), ODataFeed (@see ODataFeed), or an array of ODataEntries.
 * @param operation The operation that should be executed on the server side. Possible values are: <br />
 * <li>ENTRY_OPERATION_CREATE: the body contains the data of a new entry that should be created in the backend.
 * <li>ENTRY_OPERATION_UPDATE_FULL: the body contains the data of an existing entry in the backend. All the updatable fields will be updated in the backend.
 * If an updatable field does not appear in the body, the value in the backend that is assigned to the missing field will be overwritten with its default value. The entry to be updated is identified by the key fields of the body.
 * <li>ENTRY_OPERATION_UPDATE_INCREMENTAL: the body contains the data of an existing entry in the backend. Only those properties are updated in the backend that are indicated in the body and leaves anything untouched in the backend.
 * <li>ENTRY_OPERATION_ARCHIVE: Used when an entry should be saved as a file and is not sent to the server. This causes the builder to add the links (if present) too to the body.
 * <li>ENTRY_OPERATION_CREATE_MINIMAL: Works similar to ENTRY_OPERATION_CREATE except that only the fields provided make up the body.
 * <li>ENTRY_OPERATION_UPDATE_FULL_MINIMAL: Works similar to ENTRY_OPERATION_UPDATE_FULL except that only the fields provided make up the body.
 * <li>ENTRY_OPERATION_UPDATE_INCREMENTAL_MINIMAL: Works similar to ENTRY_OPERATION_UPDATE_INCREMENTAL except that only the fields provided in entry make up the body.
 *  @param serviceDocument The service document instance. See @see ODataServiceDocument and its getBaseUrl method.
 *  @param serializeInlinedEntries If the parameter value is YES, all inline entries and/or feeds will be serialized that belong to the entry being serialized(for atom only).
 *  @param buildStyle This parameter indicates whether the the body should be of type ATOM or JSON. If the payload is an entry BUILD_STYLE_ATOM_XML or BUILD_STYLE_JSON can be used, if the payload is an ODataFeed or an array of ODataEntries than BUILD_STYLE_ATOM_FEED can be used. Other variations provide nil return content.
 * @return Returns the atom/json representation of an entry for the given operation and the HTTP method that must be used when sending the entry to a SAP server in an HTTP request. DO NOT USE BUILD_STYLE_ATOM_FEED!
 * @example Creating a atom/json from an entry that can be sent to the server to create or update the data in the backend defined by the key values.
 * <code>
 *  ODataEntryBody *body = buildODataEntryRequestBody(payload, TEN_ENTRY_OPERATIONS<type>, svcDoc, YES, BUILD_STYLE<type>);
 *  NSString *entryBody = body.body;
 * </code>
 */

ODataEntryBody* buildODataEntryRequestBody(const NSObject* payload, const enum TEN_ENTRY_OPERATIONS operation,
                                  const ODataServiceDocument* const serviceDocument,
                                  const BOOL serializeInlinedEntries, const enum BUILD_STYLE buildStyle);

/**
 Set the Incremental Update and Incremental Update Minimal opreation http method to PATCH based on the specification of OData 3.0
*/
void enablePatchSupport(const BOOL enable);
