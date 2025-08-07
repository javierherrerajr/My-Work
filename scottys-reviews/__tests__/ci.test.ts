import "@testing-library/jest-dom";

describe("CI Environment", () => {
  it("should pass basic test", () => {
    expect(true).toBe(true);
  });

  it("should have access to environment variables", () => {
    expect(process.env.NODE_ENV).toBeDefined();
  });
});
