const nextJest = require("next/jest");

const createJestConfig = nextJest({
  // 指向 Next.js 应用的路径
  dir: "./",
});

// Jest 配置
const customJestConfig = {
  setupFilesAfterEnv: ["<rootDir>/jest.setup.js"],
  testEnvironment: "jsdom",
  moduleNameMapper: {
    "^@/(.*)$": "<rootDir>/$1",
    "^swiper/css.*$": "<rootDir>/__mocks__/styleMock.js"
  },
  testMatch: ["**/__tests__/**/*.test.[jt]s?(x)"],
  collectCoverageFrom: [
    "app/**/*.{js,jsx,ts,tsx}",
    "components/**/*.{js,jsx,ts,tsx}",
    "lib/**/*.{js,jsx,ts,tsx}",
    "!**/*.d.ts",
    "!**/node_modules/**",
  ],
  moduleDirectories: ["node_modules", "<rootDir>/"],
  testPathIgnorePatterns: ["<rootDir>/node_modules/", "<rootDir>/.next/"],
  transformIgnorePatterns: [
    "/node_modules/(?!(lucide-react|swiper)/)",
    "^.+\\.module\\.(css|sass|scss)$",
  ],
};

module.exports = createJestConfig(customJestConfig);