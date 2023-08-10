CREATE DATABASE BAI;
use BAI;
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
                           `id` int(11) NOT NULL AUTO_INCREMENT,
                           `class` int(11) DEFAULT NULL,
                           `chinese` int(11) DEFAULT NULL,
                           `english` int(11) DEFAULT NULL,
                           `math` int(11) DEFAULT NULL,
                           `name` varchar(20) DEFAULT NULL,
                           `age` int(11) DEFAULT NULL,
                           `time` date DEFAULT NULL,
                           `sex` char(255) DEFAULT NULL,
                           PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
