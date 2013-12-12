/*
 * OpenEMU Auth with IP2Nation
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL DEFAULT '',
  `sha_pass_hash` varchar(40) NOT NULL DEFAULT '',
  `sessionkey` varchar(80) NOT NULL DEFAULT '',
  `v` varchar(64) NOT NULL DEFAULT '',
  `s` varchar(64) NOT NULL DEFAULT '',
  `email` varchar(254) NOT NULL DEFAULT '',
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `failed_logins` int(10) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `lock_country` varchar(2) NOT NULL DEFAULT '00',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `expansion` tinyint(4) unsigned NOT NULL DEFAULT '4',
  `mutetime` bigint(20) NOT NULL DEFAULT '0',
  `mutereason` varchar(255) NOT NULL DEFAULT '',
  `muteby` varchar(50) NOT NULL DEFAULT '',
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(3) NOT NULL DEFAULT '',
  `recruiter` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COMMENT='Account System';

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO account VALUES ('5', 'ADMINS', '1B5E796ABB4ED9AA505E583CAACCCA2346D971BD', '08ED0082A77C8E85B1CF9A2B6459EB5CE01284ABC82F2BB7B14AC81071D790F8286F49419BBD7F45', '078A90EED45CE0700491D50B11B0AF6E57357B59DFB7CE25F4F70BA744558F3A', 'B1662A9FCEEF4708E1CCC2F26A53290730F6EB08F0DA7F933A0C3EC925EB1CEB', 'admin@yourserver.com', '2013-10-07 10:35:37', '127.0.0.1', '0', '0', '00', '2013-10-20 09:01:57', '0', '4', '0', '', '', '2', 'Win', '0');

-- ----------------------------
-- Table structure for `account_access`
-- ----------------------------
DROP TABLE IF EXISTS `account_access`;
CREATE TABLE `account_access` (
  `id` int(10) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of account_access
-- ----------------------------

-- ----------------------------
-- Table structure for `account_banned`
-- ----------------------------
DROP TABLE IF EXISTS `account_banned`;
CREATE TABLE `account_banned` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` int(10) unsigned NOT NULL DEFAULT '0',
  `unbandate` int(10) unsigned NOT NULL DEFAULT '0',
  `bannedby` varchar(50) NOT NULL,
  `banreason` varchar(255) NOT NULL,
  `active` tinyint(3) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Ban List';

-- ----------------------------
-- Records of account_banned
-- ----------------------------

-- ----------------------------
-- Table structure for `autobroadcast`
-- ----------------------------
DROP TABLE IF EXISTS `autobroadcast`;
CREATE TABLE `autobroadcast` (
  `realmid` int(11) NOT NULL DEFAULT '-1',
  `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `weight` tinyint(3) unsigned DEFAULT '1',
  `text` longtext NOT NULL,
  PRIMARY KEY (`id`,`realmid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of autobroadcast
-- ----------------------------

-- ----------------------------
-- Table structure for `ip2nation`
-- ----------------------------
DROP TABLE IF EXISTS `ip2nation`;
CREATE TABLE `ip2nation` (
  `ip` int(11) unsigned NOT NULL DEFAULT '0',
  `country` char(2) NOT NULL DEFAULT '',
  KEY `ip` (`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ip2nation
-- ----------------------------
INSERT INTO ip2nation VALUES ('0', 'us');
-- ----------------------------
-- Table structure for `ip2nationcountries`
-- ----------------------------
DROP TABLE IF EXISTS `ip2nationcountries`;
CREATE TABLE `ip2nationcountries` (
  `code` varchar(4) NOT NULL DEFAULT '',
  `iso_code_2` varchar(2) NOT NULL DEFAULT '',
  `iso_code_3` varchar(3) DEFAULT '',
  `iso_country` varchar(255) NOT NULL DEFAULT '',
  `country` varchar(255) NOT NULL DEFAULT '',
  `lat` float NOT NULL DEFAULT '0',
  `lon` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`code`),
  KEY `code` (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ip2nationcountries
-- ----------------------------
INSERT INTO ip2nationcountries VALUES ('01', '', '', '', 'Private', '0', '0');
INSERT INTO ip2nationcountries VALUES ('ad', 'AN', 'AND', 'Andorra', 'Andorra', '42.3', '1.3');
INSERT INTO ip2nationcountries VALUES ('ae', 'AR', 'ARE', 'United Arab Emirates', 'United Arab Emirates', '24', '54');
INSERT INTO ip2nationcountries VALUES ('af', 'AF', 'AFG', 'Afghanistan', 'Afghanistan', '33', '65');
INSERT INTO ip2nationcountries VALUES ('ag', 'AT', 'ATG', 'Antigua and Barbuda', 'Antigua and Barbuda', '17.03', '-61.48');
INSERT INTO ip2nationcountries VALUES ('ai', 'AI', 'AIA', 'Anguilla', 'Anguilla', '18.15', '-63.1');
INSERT INTO ip2nationcountries VALUES ('al', 'AL', 'ALB', 'Albania', 'Albania', '41', '20');
INSERT INTO ip2nationcountries VALUES ('am', 'AR', 'ARM', 'Armenia', 'Armenia', '40', '45');
INSERT INTO ip2nationcountries VALUES ('an', 'AN', 'ANT', 'Netherlands Antilles', 'Netherlands Antilles', '12.15', '-68.45');
INSERT INTO ip2nationcountries VALUES ('ao', 'AG', 'AGO', 'Angola', 'Angola', '-12.3', '18.3');
INSERT INTO ip2nationcountries VALUES ('ap', '', '', '', 'Asia-Pacific', '-2.81', '128.5');
INSERT INTO ip2nationcountries VALUES ('aq', 'AT', 'ATA', 'Antarctica', 'Antarctica', '-90', '0');
INSERT INTO ip2nationcountries VALUES ('ar', 'AR', 'ARG', 'Argentina', 'Argentina', '-34', '-64');
INSERT INTO ip2nationcountries VALUES ('as', 'AS', 'ASM', 'American Samoa', 'American Samoa', '-14.2', '-170');
INSERT INTO ip2nationcountries VALUES ('at', 'AU', 'AUT', 'Austria', 'Austria', '47.2', '13.2');
INSERT INTO ip2nationcountries VALUES ('au', 'AU', 'AUS', 'Australia', 'Australia', '-27', '133');
INSERT INTO ip2nationcountries VALUES ('aw', 'AB', 'ABW', 'Aruba', 'Aruba', '12.3', '-69.58');
INSERT INTO ip2nationcountries VALUES ('ax', 'AX', 'ALA', 'Aland Islands', 'Aland Islands', '60.21', '20.16');
INSERT INTO ip2nationcountries VALUES ('az', 'AZ', 'AZE', 'Azerbaijan', 'Azerbaijan', '40.3', '47.3');
INSERT INTO ip2nationcountries VALUES ('ba', 'BI', 'BIH', 'Bosnia and Herzegovina', 'Bosnia and Herzegovina', '44', '18');
INSERT INTO ip2nationcountries VALUES ('bb', 'BR', 'BRB', 'Barbados', 'Barbados', '13.1', '-59.32');
INSERT INTO ip2nationcountries VALUES ('bd', 'BG', 'BGD', 'Bangladesh', 'Bangladesh', '24', '90');
INSERT INTO ip2nationcountries VALUES ('be', 'BE', 'BEL', 'Belgium', 'Belgium', '50.5', '4');
INSERT INTO ip2nationcountries VALUES ('bf', 'BF', 'BFA', 'Burkina Faso', 'Burkina Faso', '13', '-2');
INSERT INTO ip2nationcountries VALUES ('bg', 'BG', 'BGR', 'Bulgaria', 'Bulgaria', '43', '25');
INSERT INTO ip2nationcountries VALUES ('bh', 'BH', 'BHR', 'Bahrain', 'Bahrain', '26', '50.33');
INSERT INTO ip2nationcountries VALUES ('bi', 'BD', 'BDI', 'Burundi', 'Burundi', '-3.3', '30');
INSERT INTO ip2nationcountries VALUES ('bj', 'BE', 'BEN', 'Benin', 'Benin', '9.3', '2.15');
INSERT INTO ip2nationcountries VALUES ('bm', 'BM', 'BMU', 'Bermuda', 'Bermuda', '32.2', '-64.45');
INSERT INTO ip2nationcountries VALUES ('bn', 'BR', 'BRN', 'Brunei Darussalam', 'Brunei Darussalam', '4.3', '114.4');
INSERT INTO ip2nationcountries VALUES ('bo', 'BO', 'BOL', 'Bolivia', 'Bolivia', '-17', '-65');
INSERT INTO ip2nationcountries VALUES ('br', 'BR', 'BRA', 'Brazil', 'Brazil', '-10', '-55');
INSERT INTO ip2nationcountries VALUES ('bs', 'BH', 'BHS', 'Bahamas', 'Bahamas', '24.15', '-76');
INSERT INTO ip2nationcountries VALUES ('bt', 'BT', 'BTN', 'Bhutan', 'Bhutan', '27.3', '90.3');
INSERT INTO ip2nationcountries VALUES ('bv', 'BV', 'BVT', 'Bouvet Island', 'Bouvet Island', '-54.26', '3.24');
INSERT INTO ip2nationcountries VALUES ('bw', 'BW', 'BWA', 'Botswana', 'Botswana', '-22', '24');
INSERT INTO ip2nationcountries VALUES ('by', 'BL', 'BLR', 'Belarus', 'Belarus', '53', '28');
INSERT INTO ip2nationcountries VALUES ('bz', 'BL', 'BLZ', 'Belize', 'Belize', '17.15', '-88.45');
INSERT INTO ip2nationcountries VALUES ('ca', 'CA', 'CAN', 'Canada', 'Canada', '60', '-95');
INSERT INTO ip2nationcountries VALUES ('cc', 'CC', 'CCK', 'Cocos (Keeling) Islands', 'Cocos (Keeling) Islands', '-12.3', '96.5');
INSERT INTO ip2nationcountries VALUES ('cd', 'CD', 'COD', 'Congo, Democratic Republic of the', 'Democratic Republic of Congo', '-4.04', '30.75');
INSERT INTO ip2nationcountries VALUES ('cf', 'CA', 'CAF', 'Central African Republic', 'Central African Republic', '7', '21');
INSERT INTO ip2nationcountries VALUES ('cg', 'CO', 'COG', 'Congo', 'Congo', '0', '25');
INSERT INTO ip2nationcountries VALUES ('ch', 'CH', 'CHE', 'Switzerland', 'Switzerland', '47', '8');
INSERT INTO ip2nationcountries VALUES ('ci', 'CI', 'CIV', 'Cote D’ivoire', 'Ivory Coast', '7.64', '-4.93');
INSERT INTO ip2nationcountries VALUES ('ck', 'CO', 'COK', 'Cook Islands', 'Cook Islands', '-21.14', '-159.46');
INSERT INTO ip2nationcountries VALUES ('cl', 'CH', 'CHL', 'Chile', 'Chile', '-30', '-71');
INSERT INTO ip2nationcountries VALUES ('cm', 'CM', 'CMR', 'Cameroon', 'Cameroon', '6', '12');
INSERT INTO ip2nationcountries VALUES ('cn', 'CH', 'CHN', 'China', 'China', '35', '105');
INSERT INTO ip2nationcountries VALUES ('co', 'CO', 'COL', 'Colombia', 'Colombia', '4', '-72');
INSERT INTO ip2nationcountries VALUES ('cr', 'CR', 'CRI', 'Costa Rica', 'Costa Rica', '10', '-84');
INSERT INTO ip2nationcountries VALUES ('cs', 'SC', 'SCG', 'Serbia and Montenegro', 'Serbia and Montenegro', '43.57', '21.41');
INSERT INTO ip2nationcountries VALUES ('cu', 'CU', 'CUB', 'Cuba', 'Cuba', '21.3', '-80');
INSERT INTO ip2nationcountries VALUES ('cv', 'CP', 'CPV', 'Cape Verde', 'Cape Verde', '16', '-24');
INSERT INTO ip2nationcountries VALUES ('cx', 'CX', 'CXR', 'Christmas Island', 'Christmas Island', '-10.3', '105.4');
INSERT INTO ip2nationcountries VALUES ('cy', 'CY', 'CYP', 'Cyprus', 'Cyprus', '35', '33');
INSERT INTO ip2nationcountries VALUES ('cz', 'CZ', 'CZE', 'Czech Republic', 'Czech Republic', '49.45', '15.3');
INSERT INTO ip2nationcountries VALUES ('de', 'DE', 'DEU', 'Germany', 'Germany', '51', '9');
INSERT INTO ip2nationcountries VALUES ('dj', 'DJ', 'DJI', 'Djibouti', 'Djibouti', '11.3', '43');
INSERT INTO ip2nationcountries VALUES ('dk', 'DN', 'DNK', 'Denmark', 'Denmark', '56', '10');
INSERT INTO ip2nationcountries VALUES ('dm', 'DM', 'DMA', 'Dominica', 'Dominica', '15.25', '-61.2');
INSERT INTO ip2nationcountries VALUES ('do', 'DO', 'DOM', 'Dominican Republic', 'Dominican Republic', '19', '-70.4');
INSERT INTO ip2nationcountries VALUES ('dz', 'DZ', 'DZA', 'Algeria', 'Algeria', '28', '3');
INSERT INTO ip2nationcountries VALUES ('ec', 'EC', 'ECU', 'Ecuador', 'Ecuador', '-2', '-77.3');
INSERT INTO ip2nationcountries VALUES ('ee', 'ES', 'EST', 'Estonia', 'Estonia', '59', '26');
INSERT INTO ip2nationcountries VALUES ('eg', 'EG', 'EGY', 'Egypt', 'Egypt', '27', '30');
INSERT INTO ip2nationcountries VALUES ('eh', 'ES', 'ESH', 'Western Sahara', 'Western Sahara', '24.3', '-13');
INSERT INTO ip2nationcountries VALUES ('er', 'ER', 'ERI', 'Eritrea', 'Eritrea', '15', '39');
INSERT INTO ip2nationcountries VALUES ('es', 'ES', 'ESP', 'Spain', 'Spain', '40', '-4');
INSERT INTO ip2nationcountries VALUES ('et', 'ET', 'ETH', 'Ethiopia', 'Ethiopia', '8', '38');
INSERT INTO ip2nationcountries VALUES ('eu', '', '', '', 'Europe', '0', '0');
INSERT INTO ip2nationcountries VALUES ('fi', 'FI', 'FIN', 'Finland', 'Finland', '64', '26');
INSERT INTO ip2nationcountries VALUES ('fj', 'FJ', 'FJI', 'Fiji', 'Fiji', '-18', '175');
INSERT INTO ip2nationcountries VALUES ('fk', 'FL', 'FLK', 'Falkland Islands (Malvinas)', 'Falkland Islands (Malvinas)', '-51.45', '-59');
INSERT INTO ip2nationcountries VALUES ('fm', 'FS', 'FSM', 'Micronesia', 'Micronesia', '6.55', '158.15');
INSERT INTO ip2nationcountries VALUES ('fo', 'FR', 'FRO', 'Faroe Islands', 'Faroe Islands', '62', '-7');
INSERT INTO ip2nationcountries VALUES ('fr', 'FR', 'FRA', 'France', 'France', '46', '2');
INSERT INTO ip2nationcountries VALUES ('ga', 'GA', 'GAB', 'Gabon', 'Gabon', '-1', '11.45');
INSERT INTO ip2nationcountries VALUES ('gd', 'GR', 'GRD', 'Grenada', 'Grenada', '12.07', '-61.4');
INSERT INTO ip2nationcountries VALUES ('ge', 'GE', 'GEO', 'Georgia', 'Georgia', '42', '43.3');
INSERT INTO ip2nationcountries VALUES ('gf', 'GU', 'GUF', 'French Guiana', 'French Guiana', '4', '-53');
INSERT INTO ip2nationcountries VALUES ('gh', 'GH', 'GHA', 'Ghana', 'Ghana', '8', '-2');
INSERT INTO ip2nationcountries VALUES ('gi', 'GI', 'GIB', 'Gibraltar', 'Gibraltar', '36.8', '-5.21');
INSERT INTO ip2nationcountries VALUES ('gl', 'GR', 'GRL', 'Greenland', 'Greenland', '72', '-40');
INSERT INTO ip2nationcountries VALUES ('gm', 'GM', 'GMB', 'Gambia', 'Gambia', '13.28', '-16.34');
INSERT INTO ip2nationcountries VALUES ('gn', 'GI', 'GIN', 'Guinea', 'Guinea', '11', '-10');
INSERT INTO ip2nationcountries VALUES ('gp', 'GL', 'GLP', 'Guadeloupe', 'Guadeloupe', '16.15', '-61.35');
INSERT INTO ip2nationcountries VALUES ('gq', 'GN', 'GNQ', 'Equatorial Guinea', 'Equatorial Guinea', '2', '10');
INSERT INTO ip2nationcountries VALUES ('gr', 'GR', 'GRC', 'Greece', 'Greece', '39', '22');
INSERT INTO ip2nationcountries VALUES ('gs', 'SG', 'SGS', 'South Georgia and the South Sandwich Islands', 'S. Georgia and S. Sandwich Isls.', '-54.3', '-37');
INSERT INTO ip2nationcountries VALUES ('gt', 'GT', 'GTM', 'Guatemala', 'Guatemala', '15.3', '-90.15');
INSERT INTO ip2nationcountries VALUES ('gu', 'GU', 'GUM', 'Guam', 'Guam', '13.28', '144.47');
INSERT INTO ip2nationcountries VALUES ('gw', 'GN', 'GNB', 'Guinea-Bissau', 'Guinea-Bissau', '12', '-15');
INSERT INTO ip2nationcountries VALUES ('gy', 'GU', 'GUY', 'Guyana', 'Guyana', '5', '-59');
INSERT INTO ip2nationcountries VALUES ('hk', 'HK', 'HKG', 'Hong Kong', 'Hong Kong', '22.15', '114.1');
INSERT INTO ip2nationcountries VALUES ('hm', 'HM', 'HMD', 'Heard Island and Mcdonald Islands', 'Heard and McDonald Islands', '-53.06', '72.31');
INSERT INTO ip2nationcountries VALUES ('hn', 'HN', 'HND', 'Honduras', 'Honduras', '15', '-86.3');
INSERT INTO ip2nationcountries VALUES ('hr', 'HR', 'HRV', 'Croatia (Hrvatska)', 'Croatia (Hrvatska)', '45.1', '15.3');
INSERT INTO ip2nationcountries VALUES ('ht', 'HT', 'HTI', 'Haiti', 'Haiti', '19', '-72.25');
INSERT INTO ip2nationcountries VALUES ('hu', 'HU', 'HUN', 'Hungary', 'Hungary', '47', '20');
INSERT INTO ip2nationcountries VALUES ('id', 'ID', 'IDN', 'Indonesia', 'Indonesia', '-5', '120');
INSERT INTO ip2nationcountries VALUES ('ie', 'IR', 'IRL', 'Ireland', 'Ireland', '53', '-8');
INSERT INTO ip2nationcountries VALUES ('il', 'IS', 'ISR', 'Israel', 'Israel', '31.3', '34.45');
INSERT INTO ip2nationcountries VALUES ('in', 'IN', 'IND', 'India', 'India', '20', '77');
INSERT INTO ip2nationcountries VALUES ('io', 'IO', 'IOT', 'British Indian Ocean Territory', 'British Indian Ocean Territory', '-6', '71.3');
INSERT INTO ip2nationcountries VALUES ('iq', 'IR', 'IRQ', 'Iraq', 'Iraq', '33', '44');
INSERT INTO ip2nationcountries VALUES ('ir', 'IR', 'IRN', 'Iran, Islamic Republic of', 'Iran', '32', '53');
INSERT INTO ip2nationcountries VALUES ('is', 'IS', 'ISL', 'Iceland', 'Iceland', '65', '-18');
INSERT INTO ip2nationcountries VALUES ('it', 'IT', 'ITA', 'Italy', 'Italy', '42.5', '12.5');
INSERT INTO ip2nationcountries VALUES ('jm', 'JA', 'JAM', 'Jamaica', 'Jamaica', '18.15', '-77.3');
INSERT INTO ip2nationcountries VALUES ('jo', 'JO', 'JOR', 'Jordan', 'Jordan', '31', '36');
INSERT INTO ip2nationcountries VALUES ('jp', 'JP', 'JPN', 'Japan', 'Japan', '36', '138');
INSERT INTO ip2nationcountries VALUES ('ke', 'KE', 'KEN', 'Kenya', 'Kenya', '1', '38');
INSERT INTO ip2nationcountries VALUES ('kg', 'KG', 'KGZ', 'Kyrgyzstan', 'Kyrgyzstan', '41', '75');
INSERT INTO ip2nationcountries VALUES ('kh', 'KH', 'KHM', 'Cambodia', 'Cambodia', '13', '105');
INSERT INTO ip2nationcountries VALUES ('ki', 'KI', 'KIR', 'Kiribati', 'Kiribati', '1.25', '173');
INSERT INTO ip2nationcountries VALUES ('km', 'CO', 'COM', 'Comoros', 'Comoros', '-12.1', '44.15');
INSERT INTO ip2nationcountries VALUES ('kn', 'KN', 'KNA', 'Saint Kitts and Nevis', 'Saint Kitts and Nevis', '17.2', '-62.45');
INSERT INTO ip2nationcountries VALUES ('kp', 'PR', 'PRK', 'Korea, Democratic People’s Republic of (North)', 'Korea (North)', '40', '127');
INSERT INTO ip2nationcountries VALUES ('kr', 'KO', 'KOR', 'Korea, Republic of (South)', 'Korea (South)', '37', '127.3');
INSERT INTO ip2nationcountries VALUES ('kw', 'KW', 'KWT', 'Kuwait', 'Kuwait', '29.3', '45.45');
INSERT INTO ip2nationcountries VALUES ('ky', 'CY', 'CYM', 'Cayman Islands', 'Cayman Islands', '19.3', '-80.3');
INSERT INTO ip2nationcountries VALUES ('kz', 'KA', 'KAZ', 'Kazakhstan', 'Kazakhstan', '48', '68');
INSERT INTO ip2nationcountries VALUES ('la', 'LA', 'LAO', 'Lao People’s Democratic Republic', 'Laos', '18', '105');
INSERT INTO ip2nationcountries VALUES ('lb', 'LB', 'LBN', 'Lebanon', 'Lebanon', '33.5', '35.5');
INSERT INTO ip2nationcountries VALUES ('lc', 'LC', 'LCA', 'Saint Lucia', 'Saint Lucia', '13.53', '-60.68');
INSERT INTO ip2nationcountries VALUES ('li', 'LI', 'LIE', 'Liechtenstein', 'Liechtenstein', '47.16', '9.32');
INSERT INTO ip2nationcountries VALUES ('lk', 'LK', 'LKA', 'Sri Lanka', 'Sri Lanka', '7', '81');
INSERT INTO ip2nationcountries VALUES ('lr', 'LB', 'LBR', 'Liberia', 'Liberia', '6.3', '-9.3');
INSERT INTO ip2nationcountries VALUES ('ls', 'LS', 'LSO', 'Lesotho', 'Lesotho', '-29.3', '28.3');
INSERT INTO ip2nationcountries VALUES ('lt', 'LT', 'LTU', 'Lithuania', 'Lithuania', '56', '24');
INSERT INTO ip2nationcountries VALUES ('lu', 'LU', 'LUX', 'Luxembourg', 'Luxembourg', '49.45', '6.1');
INSERT INTO ip2nationcountries VALUES ('lv', 'LV', 'LVA', 'Latvia', 'Latvia', '57', '25');
INSERT INTO ip2nationcountries VALUES ('ly', 'LB', 'LBY', 'Libyan Arab Jamahiriya', 'Libya', '25', '17');
INSERT INTO ip2nationcountries VALUES ('ma', 'MA', 'MAR', 'Morocco', 'Morocco', '32', '-5');
INSERT INTO ip2nationcountries VALUES ('mc', 'MC', 'MCO', 'Monaco', 'Monaco', '43.44', '7.24');
INSERT INTO ip2nationcountries VALUES ('md', 'MD', 'MDA', 'Moldova', 'Moldova', '47', '29');
INSERT INTO ip2nationcountries VALUES ('me', 'ME', 'MNE', 'Montenegro', 'Montenegro', '42.74', '19.31');
INSERT INTO ip2nationcountries VALUES ('mg', 'MD', 'MDG', 'Madagascar', 'Madagascar', '-20', '47');
INSERT INTO ip2nationcountries VALUES ('mh', 'MH', 'MHL', 'Marshall Islands', 'Marshall Islands', '9', '168');
INSERT INTO ip2nationcountries VALUES ('mk', 'MK', 'MKD', 'Macedonia, the Former Yugoslav Republic of', 'Macedonia', '41.5', '22');
INSERT INTO ip2nationcountries VALUES ('ml', 'ML', 'MLI', 'Mali', 'Mali', '17', '-4');
INSERT INTO ip2nationcountries VALUES ('mm', 'MM', 'MMR', 'Myanmar', 'Burma (Myanmar)', '22', '98');
INSERT INTO ip2nationcountries VALUES ('mn', 'MN', 'MNG', 'Mongolia', 'Mongolia', '46', '105');
INSERT INTO ip2nationcountries VALUES ('mo', 'MO', 'MAC', 'Macau', 'Macau', '22.1', '113.33');
INSERT INTO ip2nationcountries VALUES ('mp', 'MN', 'MNP', 'Northern Mariana Islands', 'Northern Mariana Islands', '15.12', '145.45');
INSERT INTO ip2nationcountries VALUES ('mq', 'MT', 'MTQ', 'Martinique', 'Martinique', '14.4', '-61');
INSERT INTO ip2nationcountries VALUES ('mr', 'MR', 'MRT', 'Mauritania', 'Mauritania', '20', '-12');
INSERT INTO ip2nationcountries VALUES ('ms', 'MS', 'MSR', 'Montserrat', 'Montserrat', '16.45', '-62.12');
INSERT INTO ip2nationcountries VALUES ('mt', 'ML', 'MLT', 'Malta', 'Malta', '35.5', '14.35');
INSERT INTO ip2nationcountries VALUES ('mu', 'MU', 'MUS', 'Mauritius', 'Mauritius', '-20.17', '57.33');
INSERT INTO ip2nationcountries VALUES ('mv', 'MD', 'MDV', 'Maldives', 'Maldives', '3.15', '73');
INSERT INTO ip2nationcountries VALUES ('mw', 'MW', 'MWI', 'Malawi', 'Malawi', '-13.3', '34');
INSERT INTO ip2nationcountries VALUES ('mx', 'ME', 'MEX', 'Mexico', 'Mexico', '23', '-102');
INSERT INTO ip2nationcountries VALUES ('my', 'MY', 'MYS', 'Malaysia', 'Malaysia', '2.3', '112.3');
INSERT INTO ip2nationcountries VALUES ('mz', 'MZ', 'MOZ', 'Mozambique', 'Mozambique', '-18.15', '35');
INSERT INTO ip2nationcountries VALUES ('na', 'NA', 'NAM', 'Namibia', 'Namibia', '-22', '17');
INSERT INTO ip2nationcountries VALUES ('nc', 'NC', 'NCL', 'New Caledonia', 'New Caledonia', '-21.3', '165.3');
INSERT INTO ip2nationcountries VALUES ('ne', 'NE', 'NER', 'Niger', 'Niger', '16', '8');
INSERT INTO ip2nationcountries VALUES ('nf', 'NF', 'NFK', 'Norfolk Island', 'Norfolk Island', '-29.02', '167.57');
INSERT INTO ip2nationcountries VALUES ('ng', 'NG', 'NGA', 'Nigeria', 'Nigeria', '10', '8');
INSERT INTO ip2nationcountries VALUES ('ni', 'NI', 'NIC', 'Nicaragua', 'Nicaragua', '13', '-85');
INSERT INTO ip2nationcountries VALUES ('nl', 'NL', 'NLD', 'Netherlands', 'Netherlands', '52.3', '5.45');
INSERT INTO ip2nationcountries VALUES ('no', 'NO', 'NOR', 'Norway', 'Norway', '62', '10');
INSERT INTO ip2nationcountries VALUES ('np', 'NP', 'NPL', 'Nepal', 'Nepal', '28', '84');
INSERT INTO ip2nationcountries VALUES ('nr', 'NR', 'NRU', 'Nauru', 'Nauru', '-0.32', '166.55');
INSERT INTO ip2nationcountries VALUES ('nt', 'NT', 'NTZ', 'Neutral Zone', 'Neutral Zone', '0', '0');
INSERT INTO ip2nationcountries VALUES ('nu', 'NI', 'NIU', 'Niue', 'Niue', '-19.02', '-169.52');
INSERT INTO ip2nationcountries VALUES ('nz', 'NZ', 'NZL', 'New Zealand', 'New Zealand (Aotearoa)', '-41', '174');
INSERT INTO ip2nationcountries VALUES ('om', 'OM', 'OMN', 'Oman', 'Oman', '21', '57');
INSERT INTO ip2nationcountries VALUES ('pa', 'PA', 'PAN', 'Panama', 'Panama', '9', '-80');
INSERT INTO ip2nationcountries VALUES ('pe', 'PE', 'PER', 'Peru', 'Peru', '-10', '-76');
INSERT INTO ip2nationcountries VALUES ('pf', 'PY', 'PYF', 'French Polynesia', 'French Polynesia', '-15', '-140');
INSERT INTO ip2nationcountries VALUES ('pg', 'PN', 'PNG', 'Papua New Guinea', 'Papua New Guinea', '-6', '147');
INSERT INTO ip2nationcountries VALUES ('ph', 'PH', 'PHL', 'Philippines', 'Philippines', '13', '122');
INSERT INTO ip2nationcountries VALUES ('pk', 'PA', 'PAK', 'Pakistan', 'Pakistan', '30', '70');
INSERT INTO ip2nationcountries VALUES ('pl', 'PO', 'POL', 'Poland', 'Poland', '52', '20');
INSERT INTO ip2nationcountries VALUES ('pm', 'SP', 'SPM', 'Saint Pierre and Miquelon', 'St. Pierre and Miquelon', '46.5', '-56.2');
INSERT INTO ip2nationcountries VALUES ('pn', 'PC', 'PCN', 'Pitcairn', 'Pitcairn', '-25.04', '-130.06');
INSERT INTO ip2nationcountries VALUES ('pr', 'PR', 'PRI', 'Puerto Rico', 'Puerto Rico', '18.15', '-66.3');
INSERT INTO ip2nationcountries VALUES ('ps', 'PS', 'PSE', 'Palestinian Territory, Occupied', 'Palestinian Territory, Occupied', '31.89', '34.9');
INSERT INTO ip2nationcountries VALUES ('pt', 'PR', 'PRT', 'Portugal', 'Portugal', '39.3', '-8');
INSERT INTO ip2nationcountries VALUES ('pw', 'PL', 'PLW', 'Palau', 'Palau', '7.3', '134.3');
INSERT INTO ip2nationcountries VALUES ('py', 'PR', 'PRY', 'Paraguay', 'Paraguay', '-23', '-58');
INSERT INTO ip2nationcountries VALUES ('qa', 'QA', 'QAT', 'Qatar', 'Qatar', '25.3', '51.15');
INSERT INTO ip2nationcountries VALUES ('re', 'RE', 'REU', 'Reunion', 'Reunion', '-21.06', '55.36');
INSERT INTO ip2nationcountries VALUES ('ro', 'RO', 'ROU', 'Romania', 'Romania', '46', '25');
INSERT INTO ip2nationcountries VALUES ('rs', 'SR', 'SRB', 'Serbia', 'Republic of Serbia', '44.02', '21.01');
INSERT INTO ip2nationcountries VALUES ('ru', 'RU', 'RUS', 'Russian Federation', 'Russia', '60', '100');
INSERT INTO ip2nationcountries VALUES ('rw', 'RW', 'RWA', 'Rwanda', 'Rwanda', '-2', '30');
INSERT INTO ip2nationcountries VALUES ('sa', 'SA', 'SAU', 'Saudi Arabia', 'Saudi Arabia', '25', '45');
INSERT INTO ip2nationcountries VALUES ('sb', 'SL', 'SLB', 'Solomon Islands', 'Solomon Islands', '-8', '159');
INSERT INTO ip2nationcountries VALUES ('sc', 'SY', 'SYC', 'Seychelles', 'Seychelles', '-4.35', '55.4');
INSERT INTO ip2nationcountries VALUES ('sd', 'SD', 'SDN', 'Sudan', 'Sudan', '15', '30');
INSERT INTO ip2nationcountries VALUES ('se', 'SW', 'SWE', 'Sweden', 'Sweden', '62', '15');
INSERT INTO ip2nationcountries VALUES ('sg', 'SG', 'SGP', 'Singapore', 'Singapore', '1.22', '103.48');
INSERT INTO ip2nationcountries VALUES ('sh', 'SH', 'SHN', 'Saint Helena', 'St. Helena', '-15.56', '-5.42');
INSERT INTO ip2nationcountries VALUES ('si', 'SV', 'SVN', 'Slovenia', 'Slovenia', '46.07', '14.49');
INSERT INTO ip2nationcountries VALUES ('sj', 'SJ', 'SJM', 'Svalbard and Jan Mayen Islands', 'Svalbard and Jan Mayen Islands', '78', '20');
INSERT INTO ip2nationcountries VALUES ('sk', 'SV', 'SVK', 'Slovakia', 'Slovak Republic', '48.4', '19.3');
INSERT INTO ip2nationcountries VALUES ('sl', 'SL', 'SLE', 'Sierra Leone', 'Sierra Leone', '8.3', '-11.3');
INSERT INTO ip2nationcountries VALUES ('sm', 'SM', 'SMR', 'San Marino', 'San Marino', '43.46', '12.25');
INSERT INTO ip2nationcountries VALUES ('sn', 'SE', 'SEN', 'Senegal', 'Senegal', '14', '-14');
INSERT INTO ip2nationcountries VALUES ('so', 'SO', 'SOM', 'Somalia', 'Somalia', '10', '49');
INSERT INTO ip2nationcountries VALUES ('sr', 'SU', 'SUR', 'Suriname', 'Suriname', '4', '-56');
INSERT INTO ip2nationcountries VALUES ('st', 'ST', 'STP', 'Sao Tome and Principe', 'Sao Tome and Principe', '1', '7');
INSERT INTO ip2nationcountries VALUES ('sv', 'SL', 'SLV', 'El Salvador', 'El Salvador', '13.5', '-88.55');
INSERT INTO ip2nationcountries VALUES ('sy', 'SY', 'SYC', 'Seychelles', 'Syria', '35', '38');
INSERT INTO ip2nationcountries VALUES ('sz', 'SW', 'SWZ', 'Swaziland', 'Swaziland', '-26.3', '31.3');
INSERT INTO ip2nationcountries VALUES ('tc', 'TC', 'TCA', 'Turks and Caicos Islands', 'Turks and Caicos Islands', '21.45', '-71.35');
INSERT INTO ip2nationcountries VALUES ('td', 'TC', 'TCD', 'Chad', 'Chad', '15', '19');
INSERT INTO ip2nationcountries VALUES ('tf', 'AT', 'ATF', 'French Southern Territories', 'French Southern Territories', '-43', '67');
INSERT INTO ip2nationcountries VALUES ('tg', 'TG', 'TGO', 'Togo', 'Togo', '8', '1.1');
INSERT INTO ip2nationcountries VALUES ('th', 'TH', 'THA', 'Thailand', 'Thailand', '15', '100');
INSERT INTO ip2nationcountries VALUES ('tj', 'TJ', 'TJK', 'Tajikistan', 'Tajikistan', '39', '71');
INSERT INTO ip2nationcountries VALUES ('tk', 'TK', 'TKL', 'Tokelau', 'Tokelau', '-9', '-172');
INSERT INTO ip2nationcountries VALUES ('tl', 'TL', 'TLS', 'Timor-Leste', 'East Timor', '-8.5', '125.55');
INSERT INTO ip2nationcountries VALUES ('tm', 'TK', 'TKM', 'Turkmenistan', 'Turkmenistan', '40', '60');
INSERT INTO ip2nationcountries VALUES ('tn', 'TU', 'TUN', 'Tunisia', 'Tunisia', '34', '9');
INSERT INTO ip2nationcountries VALUES ('to', 'TO', 'TON', 'Tonga', 'Tonga', '-20', '-175');
INSERT INTO ip2nationcountries VALUES ('tr', 'TU', 'TUR', 'Turkey', 'Turkey', '39', '35');
INSERT INTO ip2nationcountries VALUES ('tt', 'TT', 'TTO', 'Trinidad and Tobago', 'Trinidad and Tobago', '11', '-61');
INSERT INTO ip2nationcountries VALUES ('tv', 'TU', 'TUV', 'Tuvalu', 'Tuvalu', '-8', '178');
INSERT INTO ip2nationcountries VALUES ('tw', 'TW', 'TWN', 'Taiwan', 'Taiwan', '23.3', '121');
INSERT INTO ip2nationcountries VALUES ('tz', 'TZ', 'TZA', 'Tanzania, United Republic of', 'Tanzania', '-6', '35');
INSERT INTO ip2nationcountries VALUES ('ua', 'UK', 'UKR', 'Ukraine', 'Ukraine', '49', '32');
INSERT INTO ip2nationcountries VALUES ('ug', 'UG', 'UGA', 'Uganda', 'Uganda', '1', '32');
INSERT INTO ip2nationcountries VALUES ('uk', 'GB', 'GBR', 'United Kingdom', 'United Kingdom', '54', '-2');
INSERT INTO ip2nationcountries VALUES ('us', 'US', 'USA', 'United States', 'United States', '38', '-97');
INSERT INTO ip2nationcountries VALUES ('uy', 'UR', 'URY', 'Uruguay', 'Uruguay', '-33', '-56');
INSERT INTO ip2nationcountries VALUES ('uz', 'UZ', 'UZB', 'Uzbekistan', 'Uzbekistan', '41', '64');
INSERT INTO ip2nationcountries VALUES ('va', 'VA', 'VAT', 'Vatican City State', 'Vatican City State (Holy See)', '41.54', '12.27');
INSERT INTO ip2nationcountries VALUES ('vc', 'VC', 'VCT', 'Saint Vincent and the Grenadines', 'Saint Vincent and the Grenadines', '13.15', '-61.12');
INSERT INTO ip2nationcountries VALUES ('ve', 'VE', 'VEN', 'Venezuela', 'Venezuela', '8', '-66');
INSERT INTO ip2nationcountries VALUES ('vg', 'VG', 'VGB', 'Virgin Islands, British', 'Virgin Islands (British)', '18.2', '-64.5');
INSERT INTO ip2nationcountries VALUES ('vi', 'VI', 'VIR', 'Virgin Islands, U.S.', 'Virgin Islands (U.S.)', '18.2', '-64.5');
INSERT INTO ip2nationcountries VALUES ('vn', 'VN', 'VNM', 'Viet Nam', 'Viet Nam', '16', '106');
INSERT INTO ip2nationcountries VALUES ('vu', 'VU', 'VUT', 'Vanuatu', 'Vanuatu', '-16', '167');
INSERT INTO ip2nationcountries VALUES ('wf', 'WL', 'WLF', 'Wallis and Futuna Islands', 'Wallis and Futuna Islands', '-13.18', '-176.12');
INSERT INTO ip2nationcountries VALUES ('ws', 'WS', 'WSM', 'Samoa', 'Samoa', '-13.35', '-172.2');
INSERT INTO ip2nationcountries VALUES ('ye', 'YE', 'YEM', 'Yemen', 'Yemen', '15', '48');
INSERT INTO ip2nationcountries VALUES ('yt', 'MY', 'MYT', 'Mayotte', 'Mayotte', '-12.5', '45.1');
INSERT INTO ip2nationcountries VALUES ('yu', 'YU', 'YUG', 'Yugoslavia', 'Yugoslavia', '44', '21');
INSERT INTO ip2nationcountries VALUES ('za', 'ZA', 'ZAF', 'South Africa', 'South Africa', '-29', '24');
INSERT INTO ip2nationcountries VALUES ('zm', 'ZM', 'ZMB', 'Zambia', 'Zambia', '-15', '30');
INSERT INTO ip2nationcountries VALUES ('zw', 'ZW', 'ZWE', 'Zimbabwe', 'Zimbabwe', '-20', '30');

-- ----------------------------
-- Table structure for `ip_banned`
-- ----------------------------
DROP TABLE IF EXISTS `ip_banned`;
CREATE TABLE `ip_banned` (
  `ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `bandate` int(10) unsigned NOT NULL,
  `unbandate` int(10) unsigned NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Banned IPs';

-- ----------------------------
-- Records of ip_banned
-- ----------------------------

-- ----------------------------
-- Table structure for `logs`
-- ----------------------------
DROP TABLE IF EXISTS `logs`;
CREATE TABLE `logs` (
  `time` int(10) unsigned NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `type` tinyint(3) unsigned NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of logs
-- ----------------------------

-- ----------------------------
-- Table structure for `rbac_account_groups`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_account_groups`;
CREATE TABLE `rbac_account_groups` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `groupId` int(10) unsigned NOT NULL COMMENT 'Group id',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`groupId`,`realmId`),
  KEY `fk__rbac_account_groups__rbac_groups` (`groupId`),
  CONSTRAINT `fk__rbac_account_groups__account` FOREIGN KEY (`accountId`) REFERENCES `account` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__rbac_account_groups__rbac_groups` FOREIGN KEY (`groupId`) REFERENCES `rbac_groups` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Account-Group relation';

-- ----------------------------
-- Records of rbac_account_groups
-- ----------------------------

-- ----------------------------
-- Table structure for `rbac_account_permissions`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_account_permissions`;
CREATE TABLE `rbac_account_permissions` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'Permission id',
  `granted` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'Granted = 1, Denied = 0',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`permissionId`,`realmId`),
  KEY `fk__rbac_account_roles__rbac_permissions` (`permissionId`),
  CONSTRAINT `fk__rbac_account_permissions__account` FOREIGN KEY (`accountId`) REFERENCES `account` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__rbac_account_roles__rbac_permissions` FOREIGN KEY (`permissionId`) REFERENCES `rbac_permissions` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Account-Permission relation';

-- ----------------------------
-- Records of rbac_account_permissions
-- ----------------------------

-- ----------------------------
-- Table structure for `rbac_account_roles`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_account_roles`;
CREATE TABLE `rbac_account_roles` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  `granted` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'Granted = 1, Denied = 0',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`roleId`,`realmId`),
  KEY `fk__rbac_account_roles__rbac_roles` (`roleId`),
  CONSTRAINT `fk__rbac_account_roles__account` FOREIGN KEY (`accountId`) REFERENCES `account` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__rbac_account_roles__rbac_roles` FOREIGN KEY (`roleId`) REFERENCES `rbac_roles` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Account-Role relation';

-- ----------------------------
-- Records of rbac_account_roles
-- ----------------------------

-- ----------------------------
-- Table structure for `rbac_groups`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_groups`;
CREATE TABLE `rbac_groups` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Group id',
  `name` varchar(100) NOT NULL COMMENT 'Group name',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Group List';

-- ----------------------------
-- Records of rbac_groups
-- ----------------------------
INSERT INTO rbac_groups VALUES ('1', 'Player');
INSERT INTO rbac_groups VALUES ('2', 'Moderator');
INSERT INTO rbac_groups VALUES ('3', 'GameMaster');
INSERT INTO rbac_groups VALUES ('4', 'Administrator');

-- ----------------------------
-- Table structure for `rbac_group_roles`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_group_roles`;
CREATE TABLE `rbac_group_roles` (
  `groupId` int(10) unsigned NOT NULL COMMENT 'group id',
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  PRIMARY KEY (`groupId`,`roleId`),
  KEY `fk__rbac_group_roles__rbac_roles` (`roleId`),
  CONSTRAINT `fk__rbac_group_roles__rbac_groups` FOREIGN KEY (`groupId`) REFERENCES `rbac_groups` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__rbac_group_roles__rbac_roles` FOREIGN KEY (`roleId`) REFERENCES `rbac_roles` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Group Role relation';

-- ----------------------------
-- Records of rbac_group_roles
-- ----------------------------
INSERT INTO rbac_group_roles VALUES ('1', '1');
INSERT INTO rbac_group_roles VALUES ('2', '2');
INSERT INTO rbac_group_roles VALUES ('3', '3');
INSERT INTO rbac_group_roles VALUES ('4', '4');
INSERT INTO rbac_group_roles VALUES ('2', '5');
INSERT INTO rbac_group_roles VALUES ('1', '6');
INSERT INTO rbac_group_roles VALUES ('1', '7');
INSERT INTO rbac_group_roles VALUES ('2', '8');
INSERT INTO rbac_group_roles VALUES ('3', '8');
INSERT INTO rbac_group_roles VALUES ('4', '8');
INSERT INTO rbac_group_roles VALUES ('2', '9');
INSERT INTO rbac_group_roles VALUES ('3', '9');
INSERT INTO rbac_group_roles VALUES ('4', '9');
INSERT INTO rbac_group_roles VALUES ('2', '10');
INSERT INTO rbac_group_roles VALUES ('3', '10');
INSERT INTO rbac_group_roles VALUES ('4', '10');
INSERT INTO rbac_group_roles VALUES ('2', '11');
INSERT INTO rbac_group_roles VALUES ('3', '11');
INSERT INTO rbac_group_roles VALUES ('4', '11');
INSERT INTO rbac_group_roles VALUES ('2', '12');
INSERT INTO rbac_group_roles VALUES ('3', '12');
INSERT INTO rbac_group_roles VALUES ('4', '12');
INSERT INTO rbac_group_roles VALUES ('2', '13');
INSERT INTO rbac_group_roles VALUES ('3', '13');
INSERT INTO rbac_group_roles VALUES ('4', '13');
INSERT INTO rbac_group_roles VALUES ('2', '14');
INSERT INTO rbac_group_roles VALUES ('3', '14');
INSERT INTO rbac_group_roles VALUES ('4', '14');
INSERT INTO rbac_group_roles VALUES ('2', '15');
INSERT INTO rbac_group_roles VALUES ('3', '15');
INSERT INTO rbac_group_roles VALUES ('4', '15');
INSERT INTO rbac_group_roles VALUES ('2', '16');
INSERT INTO rbac_group_roles VALUES ('3', '16');
INSERT INTO rbac_group_roles VALUES ('4', '16');
INSERT INTO rbac_group_roles VALUES ('2', '17');
INSERT INTO rbac_group_roles VALUES ('3', '17');
INSERT INTO rbac_group_roles VALUES ('4', '17');
INSERT INTO rbac_group_roles VALUES ('4', '18');
INSERT INTO rbac_group_roles VALUES ('2', '19');
INSERT INTO rbac_group_roles VALUES ('3', '19');
INSERT INTO rbac_group_roles VALUES ('4', '19');
INSERT INTO rbac_group_roles VALUES ('2', '20');
INSERT INTO rbac_group_roles VALUES ('3', '20');
INSERT INTO rbac_group_roles VALUES ('4', '20');
INSERT INTO rbac_group_roles VALUES ('2', '21');
INSERT INTO rbac_group_roles VALUES ('3', '21');
INSERT INTO rbac_group_roles VALUES ('4', '21');
INSERT INTO rbac_group_roles VALUES ('2', '22');
INSERT INTO rbac_group_roles VALUES ('3', '22');
INSERT INTO rbac_group_roles VALUES ('4', '22');
INSERT INTO rbac_group_roles VALUES ('4', '23');
INSERT INTO rbac_group_roles VALUES ('2', '24');
INSERT INTO rbac_group_roles VALUES ('3', '24');
INSERT INTO rbac_group_roles VALUES ('4', '24');
INSERT INTO rbac_group_roles VALUES ('2', '25');
INSERT INTO rbac_group_roles VALUES ('3', '25');
INSERT INTO rbac_group_roles VALUES ('4', '25');
INSERT INTO rbac_group_roles VALUES ('2', '26');
INSERT INTO rbac_group_roles VALUES ('3', '26');
INSERT INTO rbac_group_roles VALUES ('4', '26');
INSERT INTO rbac_group_roles VALUES ('2', '27');
INSERT INTO rbac_group_roles VALUES ('3', '27');
INSERT INTO rbac_group_roles VALUES ('4', '27');
INSERT INTO rbac_group_roles VALUES ('2', '28');
INSERT INTO rbac_group_roles VALUES ('3', '28');
INSERT INTO rbac_group_roles VALUES ('4', '28');
INSERT INTO rbac_group_roles VALUES ('2', '29');
INSERT INTO rbac_group_roles VALUES ('3', '29');
INSERT INTO rbac_group_roles VALUES ('4', '29');
INSERT INTO rbac_group_roles VALUES ('2', '30');
INSERT INTO rbac_group_roles VALUES ('3', '30');
INSERT INTO rbac_group_roles VALUES ('4', '30');
INSERT INTO rbac_group_roles VALUES ('2', '32');
INSERT INTO rbac_group_roles VALUES ('3', '32');
INSERT INTO rbac_group_roles VALUES ('4', '32');
INSERT INTO rbac_group_roles VALUES ('2', '33');
INSERT INTO rbac_group_roles VALUES ('3', '33');
INSERT INTO rbac_group_roles VALUES ('4', '33');
INSERT INTO rbac_group_roles VALUES ('1', '34');
INSERT INTO rbac_group_roles VALUES ('2', '35');
INSERT INTO rbac_group_roles VALUES ('3', '35');
INSERT INTO rbac_group_roles VALUES ('4', '35');
INSERT INTO rbac_group_roles VALUES ('2', '36');
INSERT INTO rbac_group_roles VALUES ('3', '36');
INSERT INTO rbac_group_roles VALUES ('4', '36');
INSERT INTO rbac_group_roles VALUES ('2', '37');
INSERT INTO rbac_group_roles VALUES ('3', '37');
INSERT INTO rbac_group_roles VALUES ('4', '37');
INSERT INTO rbac_group_roles VALUES ('2', '38');
INSERT INTO rbac_group_roles VALUES ('3', '38');
INSERT INTO rbac_group_roles VALUES ('4', '38');
INSERT INTO rbac_group_roles VALUES ('3', '39');
INSERT INTO rbac_group_roles VALUES ('4', '39');

-- ----------------------------
-- Table structure for `rbac_permissions`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_permissions`;
CREATE TABLE `rbac_permissions` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Permission id',
  `name` varchar(100) NOT NULL COMMENT 'Permission name',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Permission List';

-- ----------------------------
-- Records of rbac_permissions
-- ----------------------------
INSERT INTO rbac_permissions VALUES ('1', 'Instant logout');
INSERT INTO rbac_permissions VALUES ('2', 'Skip Queue');
INSERT INTO rbac_permissions VALUES ('3', 'Join Normal Battleground');
INSERT INTO rbac_permissions VALUES ('4', 'Join Random Battleground');
INSERT INTO rbac_permissions VALUES ('5', 'Join Arenas');
INSERT INTO rbac_permissions VALUES ('6', 'Join Dungeon Finder');
INSERT INTO rbac_permissions VALUES ('7', 'Player Commands (Temporal till commands moved to rbac)');
INSERT INTO rbac_permissions VALUES ('8', 'Moderator Commands (Temporal till commands moved to rbac)');
INSERT INTO rbac_permissions VALUES ('9', 'GameMaster Commands (Temporal till commands moved to rbac)');
INSERT INTO rbac_permissions VALUES ('10', 'Administrator Commands (Temporal till commands moved to rbac)');
INSERT INTO rbac_permissions VALUES ('11', 'Log GM trades');
INSERT INTO rbac_permissions VALUES ('13', 'Skip Instance required bosses check');
INSERT INTO rbac_permissions VALUES ('14', 'Skip character creation team mask check');
INSERT INTO rbac_permissions VALUES ('15', 'Skip character creation class mask check');
INSERT INTO rbac_permissions VALUES ('16', 'Skip character creation race mask check');
INSERT INTO rbac_permissions VALUES ('17', 'Skip character creation reserved name check');
INSERT INTO rbac_permissions VALUES ('18', 'Skip character creation heroic min level check');
INSERT INTO rbac_permissions VALUES ('19', 'Skip needed requirements to use channel check');
INSERT INTO rbac_permissions VALUES ('20', 'Skip disable map check');
INSERT INTO rbac_permissions VALUES ('21', 'Skip reset talents when used more than allowed check');
INSERT INTO rbac_permissions VALUES ('22', 'Skip spam chat check');
INSERT INTO rbac_permissions VALUES ('23', 'Skip over-speed ping check');
INSERT INTO rbac_permissions VALUES ('24', 'Two side faction characters on the same account');
INSERT INTO rbac_permissions VALUES ('25', 'Allow say chat between factions');
INSERT INTO rbac_permissions VALUES ('26', 'Allow channel chat between factions');
INSERT INTO rbac_permissions VALUES ('27', 'Two side mail interaction');
INSERT INTO rbac_permissions VALUES ('28', 'See two side who list');
INSERT INTO rbac_permissions VALUES ('29', 'Add friends of other faction');
INSERT INTO rbac_permissions VALUES ('30', 'Save character without delay with .save command');
INSERT INTO rbac_permissions VALUES ('31', 'Use params with .unstuck command');
INSERT INTO rbac_permissions VALUES ('32', 'Can be assigned tickets with .assign ticket command');
INSERT INTO rbac_permissions VALUES ('33', 'Notify if a command was not found');
INSERT INTO rbac_permissions VALUES ('34', 'Check if should appear in list using .gm ingame command');
INSERT INTO rbac_permissions VALUES ('35', 'See all security levels with who command');
INSERT INTO rbac_permissions VALUES ('36', 'Filter whispers');
INSERT INTO rbac_permissions VALUES ('37', 'Use staff badge in chat');
INSERT INTO rbac_permissions VALUES ('38', 'Resurrect with full Health Points');
INSERT INTO rbac_permissions VALUES ('39', 'Restore saved gm setting states');
INSERT INTO rbac_permissions VALUES ('40', 'Allows to add a gm to friend list');
INSERT INTO rbac_permissions VALUES ('41', 'Use Config option START_GM_LEVEL to assign new character level');
INSERT INTO rbac_permissions VALUES ('42', 'Allows to use CMSG_WORLD_TELEPORT opcode');
INSERT INTO rbac_permissions VALUES ('43', 'Allows to use CMSG_WHOIS opcode');
INSERT INTO rbac_permissions VALUES ('44', 'Receive global GM messages/texts');
INSERT INTO rbac_permissions VALUES ('45', 'Join channels without announce');
INSERT INTO rbac_permissions VALUES ('46', 'Change channel settings without being channel moderator');
INSERT INTO rbac_permissions VALUES ('47', 'Enables lower security than target check');
INSERT INTO rbac_permissions VALUES ('48', 'Enable IP, Last Login and EMail output in pinfo');

-- ----------------------------
-- Table structure for `rbac_roles`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_roles`;
CREATE TABLE `rbac_roles` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Role id',
  `name` varchar(100) NOT NULL COMMENT 'Role name',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Roles List';

-- ----------------------------
-- Records of rbac_roles
-- ----------------------------
INSERT INTO rbac_roles VALUES ('1', 'Player Commands');
INSERT INTO rbac_roles VALUES ('2', 'Moderator Commands');
INSERT INTO rbac_roles VALUES ('3', 'GameMaster Commands');
INSERT INTO rbac_roles VALUES ('4', 'Administrator Commands');
INSERT INTO rbac_roles VALUES ('5', 'Quick Login/Logout');
INSERT INTO rbac_roles VALUES ('6', 'Use Battleground/Arenas');
INSERT INTO rbac_roles VALUES ('7', 'Use Dungeon Finder');
INSERT INTO rbac_roles VALUES ('8', 'Log GM trades');
INSERT INTO rbac_roles VALUES ('9', 'Skip Instance required bosses check');
INSERT INTO rbac_roles VALUES ('10', 'Ticket management');
INSERT INTO rbac_roles VALUES ('11', 'Instant .save');
INSERT INTO rbac_roles VALUES ('12', 'Allow params with .unstuck');
INSERT INTO rbac_roles VALUES ('13', 'Full HP after resurrect');
INSERT INTO rbac_roles VALUES ('14', 'Appear in GM ingame list');
INSERT INTO rbac_roles VALUES ('15', 'Use staff badge in chat');
INSERT INTO rbac_roles VALUES ('16', 'Receive global GM messages/texts');
INSERT INTO rbac_roles VALUES ('17', 'Skip over-speed ping check');
INSERT INTO rbac_roles VALUES ('18', 'Allows Admin Opcodes');
INSERT INTO rbac_roles VALUES ('19', 'Two side mail interaction');
INSERT INTO rbac_roles VALUES ('20', 'Notify if a command was not found');
INSERT INTO rbac_roles VALUES ('21', 'Enables lower security than target check');
INSERT INTO rbac_roles VALUES ('22', 'Skip disable map check');
INSERT INTO rbac_roles VALUES ('23', 'Skip reset talents when used more than allowed check');
INSERT INTO rbac_roles VALUES ('24', 'Skip spam chat check');
INSERT INTO rbac_roles VALUES ('25', 'Restore saved gm setting states');
INSERT INTO rbac_roles VALUES ('26', 'Use Config option START_GM_LEVEL to assign new character level');
INSERT INTO rbac_roles VALUES ('27', 'Skip needed requirements to use channel check');
INSERT INTO rbac_roles VALUES ('28', 'Allow say chat between factions');
INSERT INTO rbac_roles VALUES ('29', 'Filter whispers');
INSERT INTO rbac_roles VALUES ('30', 'Allow channel chat between factions');
INSERT INTO rbac_roles VALUES ('31', 'Join channels without announce');
INSERT INTO rbac_roles VALUES ('32', 'Change channel settings without being channel moderator');
INSERT INTO rbac_roles VALUES ('33', 'Skip character creation checks');
INSERT INTO rbac_roles VALUES ('34', 'Two side faction characters on the same account');
INSERT INTO rbac_roles VALUES ('35', 'See two side who list');
INSERT INTO rbac_roles VALUES ('36', 'Add friends of other faction');
INSERT INTO rbac_roles VALUES ('37', 'See all security levels with who command');
INSERT INTO rbac_roles VALUES ('38', 'Allows to add a gm to friend list');
INSERT INTO rbac_roles VALUES ('39', 'Enable IP, Last Login and EMail output in pinfo');

-- ----------------------------
-- Table structure for `rbac_role_permissions`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_role_permissions`;
CREATE TABLE `rbac_role_permissions` (
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'Permission id',
  PRIMARY KEY (`roleId`,`permissionId`),
  KEY `fk__role_permissions__rbac_permissions` (`permissionId`),
  CONSTRAINT `fk__role_permissions__rbac_permissions` FOREIGN KEY (`permissionId`) REFERENCES `rbac_permissions` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__role_permissions__rbac_roles` FOREIGN KEY (`roleId`) REFERENCES `rbac_roles` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Role Permission relation';

-- ----------------------------
-- Records of rbac_role_permissions
-- ----------------------------
INSERT INTO rbac_role_permissions VALUES ('5', '1');
INSERT INTO rbac_role_permissions VALUES ('5', '2');
INSERT INTO rbac_role_permissions VALUES ('6', '3');
INSERT INTO rbac_role_permissions VALUES ('6', '4');
INSERT INTO rbac_role_permissions VALUES ('6', '5');
INSERT INTO rbac_role_permissions VALUES ('7', '6');
INSERT INTO rbac_role_permissions VALUES ('1', '7');
INSERT INTO rbac_role_permissions VALUES ('2', '8');
INSERT INTO rbac_role_permissions VALUES ('3', '9');
INSERT INTO rbac_role_permissions VALUES ('4', '10');
INSERT INTO rbac_role_permissions VALUES ('8', '11');
INSERT INTO rbac_role_permissions VALUES ('9', '13');
INSERT INTO rbac_role_permissions VALUES ('33', '14');
INSERT INTO rbac_role_permissions VALUES ('33', '15');
INSERT INTO rbac_role_permissions VALUES ('33', '16');
INSERT INTO rbac_role_permissions VALUES ('33', '17');
INSERT INTO rbac_role_permissions VALUES ('33', '18');
INSERT INTO rbac_role_permissions VALUES ('27', '19');
INSERT INTO rbac_role_permissions VALUES ('22', '20');
INSERT INTO rbac_role_permissions VALUES ('23', '21');
INSERT INTO rbac_role_permissions VALUES ('24', '22');
INSERT INTO rbac_role_permissions VALUES ('17', '23');
INSERT INTO rbac_role_permissions VALUES ('34', '24');
INSERT INTO rbac_role_permissions VALUES ('28', '25');
INSERT INTO rbac_role_permissions VALUES ('30', '26');
INSERT INTO rbac_role_permissions VALUES ('19', '27');
INSERT INTO rbac_role_permissions VALUES ('35', '28');
INSERT INTO rbac_role_permissions VALUES ('36', '29');
INSERT INTO rbac_role_permissions VALUES ('11', '30');
INSERT INTO rbac_role_permissions VALUES ('12', '31');
INSERT INTO rbac_role_permissions VALUES ('10', '32');
INSERT INTO rbac_role_permissions VALUES ('20', '33');
INSERT INTO rbac_role_permissions VALUES ('14', '34');
INSERT INTO rbac_role_permissions VALUES ('37', '35');
INSERT INTO rbac_role_permissions VALUES ('29', '36');
INSERT INTO rbac_role_permissions VALUES ('15', '37');
INSERT INTO rbac_role_permissions VALUES ('13', '38');
INSERT INTO rbac_role_permissions VALUES ('25', '39');
INSERT INTO rbac_role_permissions VALUES ('38', '40');
INSERT INTO rbac_role_permissions VALUES ('26', '41');
INSERT INTO rbac_role_permissions VALUES ('18', '42');
INSERT INTO rbac_role_permissions VALUES ('18', '43');
INSERT INTO rbac_role_permissions VALUES ('16', '44');
INSERT INTO rbac_role_permissions VALUES ('31', '45');
INSERT INTO rbac_role_permissions VALUES ('32', '46');
INSERT INTO rbac_role_permissions VALUES ('21', '47');
INSERT INTO rbac_role_permissions VALUES ('39', '48');

-- ----------------------------
-- Table structure for `rbac_security_level_groups`
-- ----------------------------
DROP TABLE IF EXISTS `rbac_security_level_groups`;
CREATE TABLE `rbac_security_level_groups` (
  `secId` int(10) unsigned NOT NULL COMMENT 'Security Level id',
  `groupId` int(10) unsigned NOT NULL COMMENT 'group id',
  PRIMARY KEY (`secId`,`groupId`),
  KEY `fk__rbac_security_level_groups__rbac_groups` (`groupId`),
  CONSTRAINT `fk__rbac_security_level_groups__rbac_groups` FOREIGN KEY (`groupId`) REFERENCES `rbac_groups` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Default groups to assign when an account is set gm level';

-- ----------------------------
-- Records of rbac_security_level_groups
-- ----------------------------
INSERT INTO rbac_security_level_groups VALUES ('0', '1');
INSERT INTO rbac_security_level_groups VALUES ('1', '1');
INSERT INTO rbac_security_level_groups VALUES ('2', '1');
INSERT INTO rbac_security_level_groups VALUES ('3', '1');
INSERT INTO rbac_security_level_groups VALUES ('1', '2');
INSERT INTO rbac_security_level_groups VALUES ('2', '2');
INSERT INTO rbac_security_level_groups VALUES ('3', '2');
INSERT INTO rbac_security_level_groups VALUES ('2', '3');
INSERT INTO rbac_security_level_groups VALUES ('3', '3');
INSERT INTO rbac_security_level_groups VALUES ('3', '4');

-- ----------------------------
-- Table structure for `realmcharacters`
-- ----------------------------
DROP TABLE IF EXISTS `realmcharacters`;
CREATE TABLE `realmcharacters` (
  `realmid` int(10) unsigned NOT NULL DEFAULT '0',
  `acctid` int(10) unsigned NOT NULL,
  `numchars` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`),
  KEY `acctid` (`acctid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Realm Character Tracker';

-- ----------------------------
-- Records of realmcharacters
-- ----------------------------
INSERT INTO realmcharacters VALUES ('1', '5', '3');

-- ----------------------------
-- Table structure for `realmlist`
-- ----------------------------
DROP TABLE IF EXISTS `realmlist`;
CREATE TABLE `realmlist` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT 'BurstEmu',
  `address` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localAddress` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localSubnetMask` varchar(255) NOT NULL DEFAULT '255.255.255.0',
  `port` smallint(5) unsigned NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `flag` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `gamebuild` int(10) unsigned NOT NULL DEFAULT '17371',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Realm System';

-- ----------------------------
-- Records of realmlist
-- ----------------------------
INSERT INTO realmlist VALUES ('1', 'OpenEmu 5.4.0', '127.0.0.1', '127.0.0.1', '255.255.255.0', '8085', '0', '0', '1', '0', '0', '17399');

-- ----------------------------
-- Table structure for `realm_classes`
-- ----------------------------
DROP TABLE IF EXISTS `realm_classes`;
CREATE TABLE `realm_classes` (
  `realmId` int(11) NOT NULL,
  `class` tinyint(4) NOT NULL COMMENT 'Class Id',
  `expansion` tinyint(4) NOT NULL COMMENT 'Expansion for class activation',
  PRIMARY KEY (`realmId`,`class`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of realm_classes
-- ----------------------------
INSERT INTO realm_classes VALUES ('1', '1', '0');
INSERT INTO realm_classes VALUES ('1', '2', '0');
INSERT INTO realm_classes VALUES ('1', '3', '0');
INSERT INTO realm_classes VALUES ('1', '4', '0');
INSERT INTO realm_classes VALUES ('1', '5', '0');
INSERT INTO realm_classes VALUES ('1', '6', '2');
INSERT INTO realm_classes VALUES ('1', '7', '0');
INSERT INTO realm_classes VALUES ('1', '8', '0');
INSERT INTO realm_classes VALUES ('1', '9', '0');
INSERT INTO realm_classes VALUES ('1', '10', '4');
INSERT INTO realm_classes VALUES ('1', '11', '0');

-- ----------------------------
-- Table structure for `realm_races`
-- ----------------------------
DROP TABLE IF EXISTS `realm_races`;
CREATE TABLE `realm_races` (
  `realmId` int(11) NOT NULL,
  `race` tinyint(4) NOT NULL COMMENT 'Race Id',
  `expansion` tinyint(4) NOT NULL COMMENT 'Expansion for race activation',
  PRIMARY KEY (`realmId`,`race`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of realm_races
-- ----------------------------
INSERT INTO realm_races VALUES ('1', '1', '0');
INSERT INTO realm_races VALUES ('1', '2', '0');
INSERT INTO realm_races VALUES ('1', '3', '0');
INSERT INTO realm_races VALUES ('1', '4', '0');
INSERT INTO realm_races VALUES ('1', '5', '0');
INSERT INTO realm_races VALUES ('1', '6', '0');
INSERT INTO realm_races VALUES ('1', '7', '0');
INSERT INTO realm_races VALUES ('1', '8', '0');
INSERT INTO realm_races VALUES ('1', '9', '3');
INSERT INTO realm_races VALUES ('1', '10', '1');
INSERT INTO realm_races VALUES ('1', '11', '1');
INSERT INTO realm_races VALUES ('1', '22', '3');
INSERT INTO realm_races VALUES ('1', '24', '4');
INSERT INTO realm_races VALUES ('1', '25', '4');
INSERT INTO realm_races VALUES ('1', '26', '4');

-- ----------------------------
-- Table structure for `uptime`
-- ----------------------------
DROP TABLE IF EXISTS `uptime`;
CREATE TABLE `uptime` (
  `realmid` int(10) unsigned NOT NULL,
  `starttime` int(10) unsigned NOT NULL DEFAULT '0',
  `uptime` int(10) unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) NOT NULL DEFAULT 'BurstEmu',
  PRIMARY KEY (`realmid`,`starttime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Uptime system';